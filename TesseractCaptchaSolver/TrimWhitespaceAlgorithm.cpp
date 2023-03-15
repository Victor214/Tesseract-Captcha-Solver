#include <memory>
#include <opencv2/opencv.hpp>
#include "TrimWhitespaceAlgorithm.hpp"

TrimWhitespaceAlgorithm::TrimWhitespaceAlgorithm()
	:Algorithm{ AlgorithmsEnum::TRIMWHITESPACE } {
	insertMaxParameterConfiguration();
}

void TrimWhitespaceAlgorithm::process(ImageResolutionQuery& imageResolutionQuery) {
	// Convert image to greyscale
	cv::Mat& image = *(imageResolutionQuery.image);
	cv::Mat invertedImage = cv::Scalar::all(255) - image;
	
	std::vector<cv::Point> coords;
	cv::findNonZero(invertedImage, coords);
	if (!coords.empty()) {
		cv::Rect bounding_box = cv::boundingRect(coords);
		cv::Mat roi{ image, cv::Rect{bounding_box.x, bounding_box.y, bounding_box.width, bounding_box.height} };
		roi.copyTo(image);
		cv::copyMakeBorder(image, image, 20, 20, 20, 20, cv::BORDER_CONSTANT, cv::Scalar(255));

		//cv::imshow("Trimmed", image);
		//cv::waitKey(0);
	}

	Algorithm::process(imageResolutionQuery);
}