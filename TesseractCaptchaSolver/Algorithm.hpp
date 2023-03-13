#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <map>
#include <memory>

#include "AlgorithmsEnum.hpp"
#include "AlgorithmsParameterEnum.hpp"
#include "ImageResolutionQuery.hpp"

class Algorithm
{
	public:
		Algorithm(AlgorithmsEnum algoEnum);
		void static addToHead(std::unique_ptr<Algorithm>& currentHead, std::unique_ptr<Algorithm>& algo);
		void static addToTail(std::unique_ptr<Algorithm>& currentHead, std::unique_ptr<Algorithm>& algo);

		int getTotalParameterCombinationAmount() const;
		void writeParameters(int currentParamCount);
		void printDebugAlgorithm() const;
		virtual void process(ImageResolutionQuery& imageResolutionQuery) = 0;
		AlgorithmsEnum getAlgorithmEnum() const;

		std::unique_ptr<Algorithm> successor;

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
