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
		void resetParameterCounters();
		std::unique_ptr<Algorithm> getAlgorithmFromEnum(AlgorithmsEnum algorithmEnum);
		bool hasCurrentChain();
		bool hasMoreParameterCombinations(const Algorithm& chain);
		bool isAlgorithmParameterCounterMaxed(const Algorithm& algo);
		void incrementParameterCounters(Algorithm& chain);
		std::unique_ptr<Algorithm> getCombinationFromId(int id);
		void adjustAlgorithmParameters(Algorithm& chain);
		void addCoreAlgorithms(std::unique_ptr<Algorithm>& chain);

		int nextId;
		std::map<AlgorithmsEnum, int> currentParameterCount;
};

#endif