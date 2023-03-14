#include <tesseract/baseapi.h>
#include "TesseractScannerAlgorithm.hpp"
#include "TesseractSingleton.hpp"
#include "Configuration.hpp"

TesseractScannerAlgorithm::TesseractScannerAlgorithm()
	:Algorithm{ AlgorithmsEnum::TESSERACTSCANNER } {
	insertMaxParameterConfiguration();
}

void TesseractScannerAlgorithm::process(ImageResolutionQuery& imageResolutionQuery) {
    // Make a singleton out of tess, and use it to scan images, so we don't need to load tesseract every time?
    cv::Mat& image = *(imageResolutionQuery.image);

	std::string result = TesseractSingleton::recognize(image);
	imageResolutionQuery.captchaProposedSolution = result;

	std::cout << "Captcha Text: " << result << std::endl;
	//cv::imshow("Final Image", image);
	//cv::waitKey(0);

	Algorithm::process(imageResolutionQuery);
}