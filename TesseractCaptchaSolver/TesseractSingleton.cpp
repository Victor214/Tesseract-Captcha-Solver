#include <memory>
#include <tesseract/baseapi.h>
#include "Configuration.hpp"
#include "TesseractSingleton.hpp"

std::unique_ptr<TesseractSingleton> TesseractSingleton::tesseractInstance{ nullptr };

TesseractSingleton::TesseractSingleton() {
	tessBaseApi.Init(Configuration::tesseractPath.c_str(), "eng", tesseract::OEM_DEFAULT);
	tessBaseApi.SetPageSegMode(tesseract::PSM_AUTO_OSD);
	tessBaseApi.SetVariable("tessedit_char_whitelist", Configuration::tesseractCharPool.c_str());
	tessBaseApi.SetVariable("debug_file", "tesseract.log");
}

TesseractSingleton& TesseractSingleton::getInstance() {
	if (tesseractInstance)
		return *tesseractInstance;
	tesseractInstance = std::unique_ptr<TesseractSingleton>(new TesseractSingleton());
	return *tesseractInstance;
}

std::string TesseractSingleton::recognize(const cv::Mat& image) {
	TesseractSingleton& tesseractSingleton{ TesseractSingleton::getInstance() };
	tesseractSingleton.tessBaseApi.SetImage(image.data, image.cols, image.rows, 1, image.cols);
	tesseractSingleton.tessBaseApi.Recognize(NULL);

	std::string text{ tesseractSingleton.tessBaseApi.GetUTF8Text() };

	// Remove Whitespaces and new lines
	text.erase(std::remove(text.begin(), text.end(), '\n'), text.cend());
	text.erase(std::remove(text.begin(), text.end(), '\r'), text.cend());

	return text;
}