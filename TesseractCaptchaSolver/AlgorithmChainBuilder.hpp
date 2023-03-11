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
		std::unique_ptr<std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>> returnNextChain();

	private:
		void resetParameterCounters();
		std::unique_ptr<Algorithm> getAlgorithmFromEnum(AlgorithmsEnum algorithmEnum);
		bool hasCurrentChain();
		bool hasMoreParameterCombinations(std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>& algos);
		bool isAlgorithmParameterCounterMaxed(Algorithm& algo);
		void incrementParameterCounters(std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>& algos);
		std::unique_ptr<std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>> getCombinationFromId(int id);
		void adjustAlgorithmParameters(std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>& algos);

		int nextId;
		std::map<AlgorithmsEnum, int> currentParameterCount;
};

#endif