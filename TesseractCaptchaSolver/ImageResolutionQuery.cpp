#include <stdexcept>
#include "ImageResolutionQuery.hpp"

ImageResolutionQuery::ImageResolutionQuery(std::string captchaSolution)
	:captchaSolution{ captchaSolution } {

}

void ImageResolutionQuery::loadImage() {
	if (captchaSolution.empty())
		throw std::invalid_argument("Captcha name is not valid");

	std::string path{ "image/" + captchaSolution + ".png" };
	image = std::make_unique<cv::Mat>(cv::imread(path, cv::IMREAD_COLOR));
}

bool ImageResolutionQuery::isCorrectSolution() const {
	if (captchaSolution.empty() || captchaProposedSolution.empty())
		throw std::invalid_argument("Provided captcha solutions are empty");

	return captchaSolution == captchaProposedSolution;
}