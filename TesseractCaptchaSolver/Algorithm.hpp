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
		void static addToHead(std::unique_ptr<Algorithm>& currentHead, std::unique_ptr<Algorithm>& algo);
		void static addToTail(std::unique_ptr<Algorithm>& currentHead, std::unique_ptr<Algorithm>& algo);

		int getTotalParameterCombinationAmount() const;
		void writeParameters(int currentParamCount);
		virtual void printDebugAlgorithm() const;
		virtual void process(ImageResolutionQuery& imageResolutionQuery);
		AlgorithmsEnum getAlgorithmEnum() const;

		std::unique_ptr<Algorithm> successor;

	protected:
		Algorithm(AlgorithmsEnum algoEnum);
		void setAlgorithmEnum(AlgorithmsEnum algorithmEnum);
		std::map<AlgorithmsParameterEnum, int> parameters;
		std::map<AlgorithmsParameterEnum, int> maxParameters;

	private:
		AlgorithmsEnum algorithmEnum;
};

struct AlgorithmCompare {
	bool operator() (const std::unique_ptr<Algorithm>& a, const std::unique_ptr<Algorithm>& b) const {
		return a->getAlgorithmEnum() < b->getAlgorithmEnum();
	}
};

#endif
