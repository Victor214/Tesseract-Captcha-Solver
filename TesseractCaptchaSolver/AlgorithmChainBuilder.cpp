#include <memory>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <unordered_set>

#include "Configuration.hpp"
#include "AlgorithmChainBuilder.hpp"
#include "AlgorithmsParameterEnum.hpp"
#include "AlgorithmFactory.hpp"

#include "ImageReaderAlgorithm.hpp"
#include "TesseractScannerAlgorithm.hpp"

AlgorithmChainBuilder::AlgorithmChainBuilder() 
	: nextId{1} {
	for (const auto algoInPool : Configuration::algorithmsPool) {
		currentParameterCount.emplace(algoInPool, 0);
	}
}

bool AlgorithmChainBuilder::hasCurrentChain() const { // Verifies if it has more variations in algorithm sequences to be called, or if work has ended.
	int maxChains{ static_cast<int>(pow(2, Configuration::algorithmsPool.size())) - 1 };
	if (nextId > maxChains)
		return false;
	return true;
}

bool AlgorithmChainBuilder::hasMoreParameterCombinations(const Algorithm& chain) const { // Verifies if has more parameter combinations, or if all parameter combinations have been exhausted for the current combination of algorithms.
	const Algorithm* current{ &chain };
	while (current != nullptr)
	{
		if (!isAlgorithmParameterCounterMaxed(*current))
			return true;
		current = (current->successor).get();
	}
	return false;
}

bool AlgorithmChainBuilder::isAlgorithmParameterCounterMaxed(const Algorithm& algo) const {
	AlgorithmsEnum algoEnum{ algo.getAlgorithmEnum() };
	int maxParamAmount{ algo.getTotalParameterCombinationAmount() };
	if (this->currentParameterCount.at(algoEnum) < maxParamAmount - 1) // If current algorithm total parameter combinations is below the max amount.
		return false;
	return true;
}

void AlgorithmChainBuilder::iterateNextCombination() {
	// Increment nextId, so a chain with different algorithms is generated
	nextId++;

	// Reset Parameter Counters
	for (auto& currParam : currentParameterCount) {
		currParam.second = 0;
	}
}


void AlgorithmChainBuilder::incrementParameterCounters(const Algorithm& chain) {
	const Algorithm* current{ &chain };
	while (current != nullptr)
	{
		AlgorithmsEnum algoEnum{ current->getAlgorithmEnum() };
		if (!isAlgorithmParameterCounterMaxed(*current)) {
			currentParameterCount[algoEnum]++;
			return;
		}

		currentParameterCount[algoEnum] = 0; // If it reached here, means the total parameter count for the current algo can't be incremented, so zero this and follow to the next one.
		current = (current->successor).get();
	}
}

std::unique_ptr<Algorithm> AlgorithmChainBuilder::getCombinationFromId(const int id) {
	std::unique_ptr<Algorithm> prev{ nullptr };
	for (int i = Configuration::algorithmsPool.size() - 1; i >= 0; i--) {
		AlgorithmsEnum algoEnum{ Configuration::algorithmsPool[i] };
		bool shouldPickAlgo{ ((id >> i) & 1) == 1 };
		if (shouldPickAlgo) {
			std::unique_ptr<Algorithm> current{ AlgorithmFactory::createAlgorithm(algoEnum) };
			Algorithm::addToHead(prev, current); // Prev is now the new head
		}
	}

	return prev;
}

void AlgorithmChainBuilder::adjustAlgorithmParameters(Algorithm& chain) {
	Algorithm* current{ &chain };
	while (current != nullptr)
	{
		AlgorithmsEnum algoEnum{ current->getAlgorithmEnum() };
		current->writeParameters(currentParameterCount[algoEnum]);
		current = (current->successor).get();
	}
}

bool AlgorithmChainBuilder::isValidCombination(const Algorithm& chain) const {
	// Convert current algorithms into a set for easy lookup
	std::unordered_set<AlgorithmsEnum> algorithmsInChain;
	const Algorithm* current{ &chain };
	while (current != nullptr)
	{
		algorithmsInChain.emplace(current->getAlgorithmEnum());
		current = (current->successor).get();
	}

	// Check for dependency rules
	for (auto dependency : Configuration::algorithmDependencyList) {
		if (algorithmsInChain.count(dependency.first) && !algorithmsInChain.count(dependency.second)) // Contains first, but not second
			return false;
	}
	return true;
}

std::unique_ptr<Algorithm> AlgorithmChainBuilder::getNextValidCombination() {
	do {
		if (!hasCurrentChain())
			return nullptr;

		std::unique_ptr<Algorithm> chain{ getCombinationFromId(nextId) }; // We know for sure this exists, but still need to make sure it is valid.
		if (isValidCombination(*chain))
			return chain;

		iterateNextCombination();
	} while (true);
}

// Adds core algorithms which are invariant, are not related to image processing, and are always required for the chain to properly work.
void AlgorithmChainBuilder::addCoreAlgorithms(std::unique_ptr<Algorithm>& chain) {
	std::unique_ptr<Algorithm> imageReader{ std::make_unique<ImageReaderAlgorithm>() };
	Algorithm::addToHead(chain, imageReader);

	std::unique_ptr<Algorithm> tesseractScanner{ std::make_unique<TesseractScannerAlgorithm>() };
	Algorithm::addToTail(chain, tesseractScanner);
}

std::unique_ptr<Algorithm> AlgorithmChainBuilder::returnNextChain() {
	std::unique_ptr<Algorithm> chain{ getNextValidCombination() };
	if (!chain) {
		return nullptr;
	}

	adjustAlgorithmParameters(*chain);
	if (!hasMoreParameterCombinations(*chain)) {
		iterateNextCombination();
	} else {
		incrementParameterCounters(*chain);
	}
	
	addCoreAlgorithms(chain);
	return chain;
}