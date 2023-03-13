#include <memory>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <set>

#include "Configuration.hpp"
#include "AlgorithmChainBuilder.hpp"
#include "AlgorithmsParameterEnum.hpp"

#include "GreyscaleAlgorithm.hpp"
#include "ContrastAlgorithm.hpp"
#include "IslandRemovalAlgorithm.hpp"
#include "ImageReaderAlgorithm.hpp"
#include "TesseractScannerAlgorithm.hpp"

AlgorithmChainBuilder::AlgorithmChainBuilder() 
	: nextId{1} {
	std::vector<AlgorithmsEnum>::const_iterator algoEnumIt;
	for (algoEnumIt = Configuration::algorithmsPool.cbegin(); algoEnumIt != Configuration::algorithmsPool.cend(); ++algoEnumIt) {
		currentParameterCount.emplace(*algoEnumIt, 0);
	}
}

void AlgorithmChainBuilder::resetParameterCounters() {
	std::map<AlgorithmsEnum, int>::iterator currParamIt;
	for (currParamIt = currentParameterCount.begin(); currParamIt != currentParameterCount.end(); ++currParamIt) {
		currParamIt->second = 0;
	}
}

std::unique_ptr<Algorithm> AlgorithmChainBuilder::getAlgorithmFromEnum(AlgorithmsEnum algorithmEnum) {
	switch (algorithmEnum)
	{
		case AlgorithmsEnum::GREYSCALE:
			return std::make_unique<GreyscaleAlgorithm>();

		case AlgorithmsEnum::ISLANDREMOVAL:
			return std::make_unique<IslandRemovalAlgorithm>();

		case AlgorithmsEnum::CONTRAST:
			return std::make_unique<ContrastAlgorithm>();

		default:
			throw std::invalid_argument("This algorithm is not implemented yet, please pass a valid algorithm.");
	}
}

bool AlgorithmChainBuilder::hasCurrentChain() { // Verifies if it has more variations in algorithm sequences to be called, or if work has ended.
	int maxChains = static_cast<int>(pow(2, Configuration::algorithmsPool.size())) - 1;
	if (nextId > maxChains)
		return false;
	return true;
}


bool AlgorithmChainBuilder::hasMoreParameterCombinations(const Algorithm& chain) { // Verifies if has more parameter combinations, or if all parameter combinations have been exhausted for the current combination of algorithms.
	const Algorithm* current = &chain;
	while (current != nullptr)
	{
		if (!isAlgorithmParameterCounterMaxed(*current))
			return true;
		current = (current->successor).get();
	}
	return false;
}

bool AlgorithmChainBuilder::isAlgorithmParameterCounterMaxed(const Algorithm& algo) {
	AlgorithmsEnum algoEnum = algo.getAlgorithmEnum();
	int maxParamAmount = algo.getTotalParameterCombinationAmount();
	if (this->currentParameterCount[algoEnum] < maxParamAmount - 1) // If current algorithm total parameter combinations is below the max amount.
		return false;
	return true;
}

void AlgorithmChainBuilder::incrementParameterCounters(Algorithm& chain) {
	const Algorithm* current = &chain;
	while (current != nullptr)
	{
		AlgorithmsEnum algoEnum = current->getAlgorithmEnum();
		if (!isAlgorithmParameterCounterMaxed(*current)) {
			currentParameterCount[algoEnum]++;
			return;
		}

		currentParameterCount[algoEnum] = 0; // If it reached here, means the total parameter count for the current algo can't be incremented, so zero this and follow to the next one.
		current = (current->successor).get();
	}
}

std::unique_ptr<Algorithm> AlgorithmChainBuilder::getCombinationFromId(int id) {
	std::unique_ptr<Algorithm> prev = nullptr;
	for (int i = Configuration::algorithmsPool.size() - 1; i >= 0; i--) {
		auto algoEnum = Configuration::algorithmsPool[i];
		bool shouldPickAlgo = ((id >> i) & 1) == 1;
		if (shouldPickAlgo) {
			std::unique_ptr<Algorithm> current = getAlgorithmFromEnum(algoEnum);
			Algorithm::addToHead(prev, current); // Prev is now the new head
		}
	}

	return prev;
}

void AlgorithmChainBuilder::adjustAlgorithmParameters(Algorithm& chain) {
	Algorithm* current = &chain;
	while (current != nullptr)
	{
		auto algoEnum = current->getAlgorithmEnum();
		current->writeParameters(currentParameterCount[algoEnum]);
		current = (current->successor).get();
	}
}

// Adds core algorithms which are invariant, are not related to image processing, and are always required for the chain to properly work.
void AlgorithmChainBuilder::addCoreAlgorithms(std::unique_ptr<Algorithm>& chain) {
	std::unique_ptr<Algorithm> imageReader = std::make_unique<ImageReaderAlgorithm>();
	Algorithm::addToHead(chain, imageReader);

	std::unique_ptr<Algorithm> tesseractScanner = std::make_unique<TesseractScannerAlgorithm>();
	Algorithm::addToTail(chain, tesseractScanner);
}

std::unique_ptr<Algorithm> AlgorithmChainBuilder::returnNextChain() {
	if (!hasCurrentChain())
		return nullptr;

	std::unique_ptr<Algorithm> chain = getCombinationFromId(nextId);

	adjustAlgorithmParameters(*chain);
	if (!hasMoreParameterCombinations(*chain)) {
		nextId++;
		resetParameterCounters();
	} else {
		incrementParameterCounters(*chain);
	}
	
	addCoreAlgorithms(chain);
	return chain;
}