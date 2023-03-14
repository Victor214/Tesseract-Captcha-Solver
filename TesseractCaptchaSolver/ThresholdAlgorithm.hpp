#ifndef GREYSCALE_THRESHOLD_ALGORITHM_HPP
#define GREYSCALE_THRESHOLD_ALGORITHM_HPP

#include "Algorithm.hpp"

class ThresholdAlgorithm : public Algorithm {
	public:
		ThresholdAlgorithm();
		virtual void process(ImageResolutionQuery& imageResolutionQuery) override;

	private:
		void insertMaxParameterConfiguration() {
			this->maxParameters.emplace(AlgorithmsParameterEnum::THRESHOLDVALUE, 5);
		}
		constexpr static int rangeCutoff = 40; // How much should the range cutoff be: if 0, ranges from 0 to 255. If 40, 40 to 215.
};

#endif