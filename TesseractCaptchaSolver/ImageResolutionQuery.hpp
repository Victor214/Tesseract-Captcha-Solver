#ifndef IMAGE_RESOLUTION_QUERY_HPP
#define IMAGE_RESOLUTION_QUERY_HPP

#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>

class ImageResolutionQuery
{
	public:
		ImageResolutionQuery(std::string captchaSolution);
		bool isCorrectSolution();
		void loadImage();

		std::unique_ptr<cv::Mat> image;

		std::string captchaSolution;
		std::string captchaProposedSolution;
};

#endif
