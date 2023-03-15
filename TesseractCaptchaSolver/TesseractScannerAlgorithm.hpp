#ifndef TESSERACT_SCANNER_ALGORITHM_HPP
#define TESSERACT_SCANNER_ALGORITHM_HPP

#include "Algorithm.hpp"

class TesseractScannerAlgorithm : public Algorithm {
public:
	TesseractScannerAlgorithm();
	virtual void process(ImageResolutionQuery& imageResolutionQuery) override;
	virtual ~TesseractScannerAlgorithm() = default;

private:
	void insertMaxParameterConfiguration() {

	}
};

#endif