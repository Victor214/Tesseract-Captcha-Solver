#ifndef IMAGE_READER_ALGORITHM_HPP
#define IMAGE_READER_ALGORITHM_HPP

#include "Algorithm.hpp"

class ImageReaderAlgorithm : public Algorithm {
public:
	ImageReaderAlgorithm();
	virtual void process(ImageResolutionQuery& imageResolutionQuery) override;

private:
	void insertMaxParameterConfiguration();
};

#endif