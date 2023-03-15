#ifndef GREYSCALE_ALGORITHM_HPP
#define GREYSCALE_ALGORITHM_HPP

#include "Algorithm.hpp"

class GreyscaleAlgorithm : public Algorithm {
	public:
		GreyscaleAlgorithm();
		virtual void process(ImageResolutionQuery& imageResolutionQuery) override;
		virtual ~GreyscaleAlgorithm() = default;

	private:
		void insertMaxParameterConfiguration() {

		}
};

#endif