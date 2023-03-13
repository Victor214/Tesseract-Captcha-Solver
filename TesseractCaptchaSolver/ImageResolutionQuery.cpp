#include <stdexcept>
#include "ImageResolutionQuery.hpp"

ImageResolutionQuery::ImageResolutionQuery(std::string path)
	:path{path} {

}

void ImageResolutionQuery::loadImage() {
	if (path.empty())
		throw std::invalid_argument("Path is not valid");

	image = std::make_unique<cv::Mat>(cv::imread(path, cv::IMREAD_COLOR));
}

bool ImageResolutionQuery::isCorrectSolution() {
	if (captchaSolution.empty() || captchaProposedSolution.empty())
		throw std::invalid_argument("Provided captcha solutions are empty");

	return captchaSolution == captchaProposedSolution;
}