#include "Algorithm.hpp"
#include "AlgorithmsParameterEnum.hpp"

Algorithm::Algorithm(AlgorithmsEnum algoEnum)
	:algorithmEnum{ algoEnum } {

}

int Algorithm::getTotalParameterCombinationAmount() {
	int total = 1;
	std::map<AlgorithmsParameterEnum, int>::iterator it;
	for (it = maxParameters.begin(); it != maxParameters.end(); ++it) {
		total *= it->second;
	}
	return total;
}

void Algorithm::writeParameters(int currentParamCount) {
	int divisor = 1;
	std::map<AlgorithmsParameterEnum, int>::iterator algoParamMaxIt;
	for (algoParamMaxIt = maxParameters.begin(); algoParamMaxIt != maxParameters.end(); ++algoParamMaxIt) {
		int maxParameterValue = algoParamMaxIt->second;
		int parameterValue = (currentParamCount / divisor) % maxParameterValue;
		parameters.emplace(algoParamMaxIt->first, parameterValue);
		divisor *= maxParameterValue;
	}
}

void Algorithm::printDebugAlgorithm() {
	std::cout << algorithmEnum << ": ";
	for (auto param : parameters) {
		std::cout << "[" << param.first << ", " << param.second << "] ";
	}
	std::cout << std::endl;
}

static bool algorithmCompare(const std::unique_ptr<Algorithm>& a, const std::unique_ptr<Algorithm>& b) {
	return a->getAlgorithmEnum() < b->getAlgorithmEnum();
}

// Gets & Sets
AlgorithmsEnum Algorithm::getAlgorithmEnum() {
	return this->algorithmEnum;
}

void Algorithm::setAlgorithmEnum(AlgorithmsEnum algorithmEnum) {
	this->algorithmEnum = algorithmEnum;
}