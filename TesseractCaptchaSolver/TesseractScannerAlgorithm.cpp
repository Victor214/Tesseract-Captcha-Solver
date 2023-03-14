#include "TesseractScannerAlgorithm.hpp"

TesseractScannerAlgorithm::TesseractScannerAlgorithm()
	:Algorithm{ AlgorithmsEnum::TESSERACTSCANNER } {
	insertMaxParameterConfiguration();
}

void TesseractScannerAlgorithm::process(ImageResolutionQuery& imageResolutionQuery) {
	Algorithm::process(imageResolutionQuery);
}