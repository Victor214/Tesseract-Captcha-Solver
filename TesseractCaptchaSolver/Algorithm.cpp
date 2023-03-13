#include "Algorithm.hpp"
#include "AlgorithmsParameterEnum.hpp"
#include "Configuration.hpp"

Algorithm::Algorithm(AlgorithmsEnum algoEnum)
	:algorithmEnum{ algoEnum }, successor{nullptr} {

}

void Algorithm::addToHead(std::unique_ptr<Algorithm>& currentHead, std::unique_ptr<Algorithm>& algo) {
	algo->successor = std::move(currentHead);
	currentHead = std::move(algo);
}

void Algorithm::addToTail(std::unique_ptr<Algorithm>& currentHead, std::unique_ptr<Algorithm>& algo) {
	Algorithm* current = currentHead.get();
	while (current->successor != nullptr) {
		current = current->successor.get();
	}

	// Current is now last element of linked list
	current->successor = std::move(algo);
}

int Algorithm::getTotalParameterCombinationAmount() const {
	int total = 1;
	std::map<AlgorithmsParameterEnum, int>::const_iterator it;
	for (it = maxParameters.cbegin(); it != maxParameters.cend(); ++it) {
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

void Algorithm::printDebugAlgorithm() const {
	std::cout << algorithmEnum << ": ";
	for (auto param : parameters) {
		std::cout << "[" << param.first << ", " << param.second << "] ";
	}
	std::cout << std::endl;
}

static bool algorithmCompare(const std::unique_ptr<Algorithm>& a, const std::unique_ptr<Algorithm>& b) {
	return a->getAlgorithmEnum() < b->getAlgorithmEnum();
}

void Algorithm::process(ImageResolutionQuery& imageResolutionQuery) {
	if (Configuration::isDebugEnabled)
		printDebugAlgorithm();

	if (successor != nullptr)
		successor->process(imageResolutionQuery);
}

// Gets & Sets
AlgorithmsEnum Algorithm::getAlgorithmEnum() const {
	return this->algorithmEnum;
}

void Algorithm::setAlgorithmEnum(AlgorithmsEnum algorithmEnum) {
	this->algorithmEnum = algorithmEnum;
}