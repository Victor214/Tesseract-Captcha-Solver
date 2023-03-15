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
	for (auto const& maxParam : maxParameters) {
		total *= maxParam.second;
	}
	return total;
}

void Algorithm::writeParameters(int currentParamCount) {
	int divisor = 1;
	for (auto const& maxParam : maxParameters) {
		int maxParameterValue = maxParam.second;
		int parameterValue = (currentParamCount / divisor) % maxParameterValue;
		parameters.emplace(maxParam.first, parameterValue);
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
	if (successor != nullptr)
		successor->process(imageResolutionQuery);
}

std::string Algorithm::getChainDescription() {
	std::stringstream description;
	const Algorithm* current = this;
	while (current != nullptr)
	{
		AlgorithmsEnum algoEnum = current->getAlgorithmEnum();
		description << algoEnum << ":";
		for (auto param : current->parameters) {
			description << " [" << param.first << ", " << param.second << "]";
		}
		description << "\n";

		current = (current->successor).get();
	}

	return description.str();
}

// Gets & Sets
AlgorithmsEnum Algorithm::getAlgorithmEnum() const {
	return this->algorithmEnum;
}

void Algorithm::setAlgorithmEnum(AlgorithmsEnum algorithmEnum) {
	this->algorithmEnum = algorithmEnum;
}