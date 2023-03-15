#include <stdexcept>
#include "AlgorithmFactory.hpp"

#include "GreyscaleAlgorithm.hpp"
#include "ThresholdAlgorithm.hpp"
#include "IslandRemovalAlgorithm.hpp"
#include "MedianFilterAlgorithm.hpp"
#include "TrimWhitespaceAlgorithm.hpp"

const std::unordered_map<AlgorithmsEnum, AlgorithmFactoryLambda> AlgorithmFactory::factoryMap {
	// Add lambda functions for the other algorithms in a similar way
	{ AlgorithmsEnum::GREYSCALE, [] { return std::make_unique<GreyscaleAlgorithm>(); } },
	{ AlgorithmsEnum::THRESHOLD, [] { return std::make_unique<ThresholdAlgorithm>(); } },
	{ AlgorithmsEnum::ISLANDREMOVAL, [] { return std::make_unique<IslandRemovalAlgorithm>(); } },
	{ AlgorithmsEnum::MEDIANFILTER, [] { return std::make_unique<MedianFilterAlgorithm>(); } },
	{ AlgorithmsEnum::TRIMWHITESPACE, [] { return std::make_unique<TrimWhitespaceAlgorithm>(); } },
};

std::unique_ptr<Algorithm> AlgorithmFactory::createAlgorithm(const AlgorithmsEnum algoEnum) {
	if (factoryMap.find(algoEnum) == factoryMap.end())
		throw std::invalid_argument("The given algorithm enum doesn't have a factory associated to it");
	return factoryMap.at(algoEnum)();
}