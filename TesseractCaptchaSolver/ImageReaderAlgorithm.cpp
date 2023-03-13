#include "Algorithm.hpp"
#include "ImageReaderAlgorithm.hpp"

ImageReaderAlgorithm::ImageReaderAlgorithm()
	:Algorithm{ AlgorithmsEnum::IMAGEREADER } {
	insertMaxParameterConfiguration();
}

void ImageReaderAlgorithm::insertMaxParameterConfiguration() {

}

void ImageReaderAlgorithm::process(ImageResolutionQuery& imageResolutionQuery) {
	imageResolutionQuery.loadImage();
	Algorithm::process(imageResolutionQuery);
}