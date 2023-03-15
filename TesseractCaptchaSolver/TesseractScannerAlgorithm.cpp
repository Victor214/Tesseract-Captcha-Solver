#include <tesseract/baseapi.h>
#include "TesseractScannerAlgorithm.hpp"
#include "TesseractSingleton.hpp"
#include "Configuration.hpp"

TesseractScannerAlgorithm::TesseractScannerAlgorithm()
	:Algorithm{ AlgorithmsEnum::TESSERACTSCANNER } {
	insertMaxParameterConfiguration();
}

void TesseractScannerAlgorithm::process(ImageResolutionQuery& imageResolutionQuery) {
	cv::Mat& image{ *(imageResolutionQuery.image) };

	std::string result{ TesseractSingleton::recognize(image) };
	imageResolutionQuery.captchaProposedSolution = result;

	if (Configuration::isDebugEnabled)
		std::cout << "Captcha Text: " << result << std::endl;
	//cv::imshow("Final Image", image);
	//cv::waitKey(0);

	Algorithm::process(imageResolutionQuery);
}