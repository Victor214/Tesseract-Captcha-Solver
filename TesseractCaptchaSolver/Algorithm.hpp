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
		AlgorithmsEnum getAlgorithmEnum() const;
		std::string getChainDescription();
		virtual void process(ImageResolutionQuery& imageResolutionQuery);

		std::unique_ptr<Algorithm> successor;

	protected:
		Algorithm(AlgorithmsEnum algoEnum);
		std::map<AlgorithmsParameterEnum, int> parameters;
		std::map<AlgorithmsParameterEnum, int> maxParameters;

	private:
		AlgorithmsEnum algorithmEnum;
};

#endif
