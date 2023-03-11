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


bool AlgorithmChainBuilder::hasMoreParameterCombinations(std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>& algos) { // Verifies if has more parameter combinations, or if all parameter combinations have been exhausted for the current combination of algorithms.
	std::set<std::unique_ptr<Algorithm>>::iterator algoIt;
	for (algoIt = algos.begin(); algoIt != algos.end(); ++algoIt) {
		if (!isAlgorithmParameterCounterMaxed(**algoIt))
			return true;
	}
	return false;
}

bool AlgorithmChainBuilder::isAlgorithmParameterCounterMaxed(Algorithm& algo) {
	AlgorithmsEnum algoEnum = algo.getAlgorithmEnum();
	int maxParamAmount = algo.getTotalParameterCombinationAmount();
	if (this->currentParameterCount[algoEnum] < maxParamAmount - 1) // If current algorithm total parameter combinations is below the max amount.
		return false;
	return true;
}

void AlgorithmChainBuilder::incrementParameterCounters(std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>& algos) {
	std::set<std::unique_ptr<Algorithm>>::iterator algoIt;
	for (algoIt = algos.begin(); algoIt != algos.end(); ++algoIt) {
		AlgorithmsEnum algoEnum = (*algoIt)->getAlgorithmEnum();
		if (!isAlgorithmParameterCounterMaxed(**algoIt)) {
			currentParameterCount[algoEnum]++;
			return;
		}

		currentParameterCount[algoEnum] = 0; // If it reached here, means the total parameter count for the current algo can't be incremented, so zero this and follow to the next one.
	}
}

std::unique_ptr<std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>> AlgorithmChainBuilder::getCombinationFromId(int id) {
	auto algorithms = std::make_unique<std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>>();
	for (int i = 0; i < Configuration::algorithmsPool.size(); i++) {
		auto algoEnum = Configuration::algorithmsPool[i];
		bool shouldPickAlgo = ((id >> i) & 1) == 1;
		if (shouldPickAlgo) {
			algorithms->emplace(
				getAlgorithmFromEnum(algoEnum));
		}
	}
	return algorithms;
}

void AlgorithmChainBuilder::adjustAlgorithmParameters(std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>& algos) {
	for(auto &algo : algos)
	{
		auto algoEnum = algo->getAlgorithmEnum();
		algo->writeParameters(currentParameterCount[algoEnum]);
	}
}

std::unique_ptr<std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>> AlgorithmChainBuilder::returnNextChain() {
	if (!hasCurrentChain())
		return nullptr;

	std::unique_ptr<std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>> algos = getCombinationFromId(nextId);
	adjustAlgorithmParameters(*algos);
	if (!hasMoreParameterCombinations(*algos)) {
		nextId++;
		resetParameterCounters();
	} else {
		incrementParameterCounters(*algos);
	}

	return algos;
}