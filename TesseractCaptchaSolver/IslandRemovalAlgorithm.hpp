#ifndef ISLAND_REMOVAL_ALGORITHM_HPP
#define ISLAND_REMOVAL_ALGORITHM_HPP

#include "Algorithm.hpp"

class IslandRemovalAlgorithm : public Algorithm {
public:
	IslandRemovalAlgorithm();
	virtual void process() override;

private:
	void insertMaxParameterConfiguration();
};

#endif