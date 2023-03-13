#ifndef CONTRAST_ALGORITHM_HPP
#define CONTRAST_ALGORITHM_HPP

#include "Algorithm.hpp"

class ContrastAlgorithm : public Algorithm {
	public:
		ContrastAlgorithm();
		virtual void process(ImageResolutionQuery& imageResolutionQuery) override;

	private:
		void insertMaxParameterConfiguration();
};

#endif