#include <memory>
#include "MedianFilterAlgorithm.hpp"

MedianFilterAlgorithm::MedianFilterAlgorithm()
	:Algorithm{ AlgorithmsEnum::MEDIANFILTER } {
	insertMaxParameterConfiguration();
}

void MedianFilterAlgorithm::process(ImageResolutionQuery& imageResolutionQuery) {
	cv::Mat& image = *(imageResolutionQuery.image);

	// Filter always needs to be an odd number
	int filterSize = minSize + (this->parameters[AlgorithmsParameterEnum::MEDIANFILTERSIZE] * 2);
	cv::medianBlur(image, image, filterSize);

	Algorithm::process(imageResolutionQuery);
}