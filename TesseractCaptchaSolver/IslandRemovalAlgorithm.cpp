#include "IslandRemovalAlgorithm.hpp"

IslandRemovalAlgorithm::IslandRemovalAlgorithm()
	:Algorithm{ AlgorithmsEnum::ISLANDREMOVAL } {
	insertMaxParameterConfiguration();
}

void IslandRemovalAlgorithm::insertMaxParameterConfiguration() {
	this->maxParameters.emplace(AlgorithmsParameterEnum::ISLANDREMOVALTHRESHOLD, 2);
	this->maxParameters.emplace(AlgorithmsParameterEnum::ISLANDREMOVALTYPE, 3);
}

void IslandRemovalAlgorithm::process() {

}