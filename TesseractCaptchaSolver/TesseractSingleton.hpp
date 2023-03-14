#ifndef TESSERACT_SINGLETON_HPP
#define TESSERACT_SINGLETON_HPP

#include <memory>
#include <opencv2/opencv.hpp>

class TesseractSingleton
{
	public:
		TesseractSingleton(const TesseractSingleton& obj) = delete; // Delete copy constructor
		static std::string recognize(const cv::Mat& image);

	private:
		TesseractSingleton();
		static TesseractSingleton& getInstance();
		static std::unique_ptr<TesseractSingleton> tesseractInstance; 
		tesseract::TessBaseAPI tessBaseApi;
};

#endif