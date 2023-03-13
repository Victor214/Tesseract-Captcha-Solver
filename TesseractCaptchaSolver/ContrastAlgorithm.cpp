#include "ContrastAlgorithm.hpp"

ContrastAlgorithm::ContrastAlgorithm()
	:Algorithm{ AlgorithmsEnum::CONTRAST } {
	insertMaxParameterConfiguration();
}

void ContrastAlgorithm::insertMaxParameterConfiguration() {
	this->maxParameters.emplace(AlgorithmsParameterEnum::CONTRASTLEVEL, 5);
}

void ContrastAlgorithm::process(ImageResolutionQuery& imageResolutionQuery) {
	Algorithm::process(imageResolutionQuery);
}