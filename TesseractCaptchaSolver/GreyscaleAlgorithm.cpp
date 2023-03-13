#include <memory>
#include "GreyscaleAlgorithm.hpp"

GreyscaleAlgorithm::GreyscaleAlgorithm() 
	:Algorithm{AlgorithmsEnum::GREYSCALE} {
	insertMaxParameterConfiguration();
}

void GreyscaleAlgorithm::insertMaxParameterConfiguration() {

}

void GreyscaleAlgorithm::process(ImageResolutionQuery& imageResolutionQuery) {
	// Convert image to greyscale
	cv::Mat& image = *(imageResolutionQuery.image);
	cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
	//cv::imshow("Greyscale", image);
	//cv::waitKey(0);

	Algorithm::process(imageResolutionQuery);
}