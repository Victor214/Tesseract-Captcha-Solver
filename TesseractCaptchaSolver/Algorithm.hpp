#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <map>
#include <memory>

#include "AlgorithmsEnum.hpp"
#include "AlgorithmsParameterEnum.hpp"

class Algorithm
{
	public:
		Algorithm(AlgorithmsEnum algoEnum);
		int getTotalParameterCombinationAmount();
		void writeParameters(int currentParamCount);
		void printDebugAlgorithm();
		virtual void process() = 0;
		
		AlgorithmsEnum getAlgorithmEnum();

		static bool algorithmCompare(std::unique_ptr<Algorithm> a, std::unique_ptr<Algorithm> b);

	protected:
		void setAlgorithmEnum(AlgorithmsEnum algorithmEnum);
		std::map<AlgorithmsParameterEnum, int> maxParameters;

	private:
		AlgorithmsEnum algorithmEnum;
		std::map<AlgorithmsParameterEnum, int> parameters;
};

struct AlgorithmCompare {
	bool operator() (const std::unique_ptr<Algorithm>& a, const std::unique_ptr<Algorithm>& b) const {
		return a->getAlgorithmEnum() < b->getAlgorithmEnum();
	}
};

#endif
