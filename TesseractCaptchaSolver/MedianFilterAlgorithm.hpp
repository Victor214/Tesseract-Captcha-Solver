#ifndef MEDIAN_FILTER_ALGORITHM_HPP
#define MEDIAN_FILTER_ALGORITHM_HPP

#include "Algorithm.hpp"

class MedianFilterAlgorithm : public Algorithm {
	public:
		MedianFilterAlgorithm();
		virtual void process(ImageResolutionQuery& imageResolutionQuery) override;
		virtual ~MedianFilterAlgorithm() = default;

	private:
		void insertMaxParameterConfiguration() {
			this->maxParameters.emplace(AlgorithmsParameterEnum::MEDIANFILTERSIZE, 3);
		}

		constexpr static int minSize = 3; // What should be the minimum size of the median filter. >>> Make sure this is always an odd number <<<
};

#endif