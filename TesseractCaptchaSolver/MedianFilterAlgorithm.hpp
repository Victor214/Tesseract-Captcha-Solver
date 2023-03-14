#ifndef MEDIAN_FILTER_ALGORITHM_HPP
#define MEDIAN_FILTER_ALGORITHM_HPP

#include "Algorithm.hpp"

class MedianFilterAlgorithm : public Algorithm {
public:
	MedianFilterAlgorithm();
	virtual void process(ImageResolutionQuery& imageResolutionQuery) override;

private:
	void insertMaxParameterConfiguration() {
		this->maxParameters.emplace(AlgorithmsParameterEnum::MEDIANFILTERSIZE, 3);
	}
};

#endif