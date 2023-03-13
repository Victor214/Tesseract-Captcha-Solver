#ifndef ISLAND_REMOVAL_ALGORITHM_HPP
#define ISLAND_REMOVAL_ALGORITHM_HPP

#include "Algorithm.hpp"

class IslandRemovalAlgorithm : public Algorithm {
public:
	IslandRemovalAlgorithm();
	virtual void process(ImageResolutionQuery& imageResolutionQuery) override;

private:
	void insertMaxParameterConfiguration();
	constexpr static int minThreshold = 5; // What should be the minimum amount to threshold. Thresholds too small may leave too much noise.
	constexpr static int maxThreshold = 20; // What should be the maximum amount to threshold. Thresholds that are too big may remove useful content.
};

#endif