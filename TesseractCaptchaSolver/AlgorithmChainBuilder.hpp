#ifndef ALGORITHMCHAINBUILDER_HPP
#define ALGORITHMCHAINBUILDER_HPP

#include <map>
#include <set>
#include "AlgorithmsEnum.hpp"
#include "Algorithm.hpp"

class AlgorithmChainBuilder
{
	public:
		AlgorithmChainBuilder();
		std::unique_ptr<Algorithm> returnNextChain();

	private:
		bool hasCurrentChain() const;
		bool hasMoreParameterCombinations(const Algorithm& chain) const;
		bool isAlgorithmParameterCounterMaxed(const Algorithm& algo) const;
		void iterateNextCombination();
		void incrementParameterCounters(const Algorithm& chain);
		std::unique_ptr<Algorithm> getCombinationFromId(const int id);
		void adjustAlgorithmParameters(Algorithm& chain);
		bool isValidCombination(const Algorithm& chain) const;
		std::unique_ptr<Algorithm> getNextValidCombination();
		void addCoreAlgorithms(std::unique_ptr<Algorithm>& chain);

		int nextId;
		std::map<AlgorithmsEnum, int> currentParameterCount;
};

#endif