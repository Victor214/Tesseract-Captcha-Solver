#include <iostream>
#include <filesystem>
#include <memory>
#include "Configuration.hpp"
#include "Algorithm.hpp"
#include "AlgorithmChainProcessor.hpp"
#include "ChainProcessingResult.hpp"

AlgorithmChainProcessor::AlgorithmChainProcessor(std::unique_ptr<Algorithm> chain) {
	this->chain = std::move(chain);
}

std::unique_ptr<ChainProcessingResult> AlgorithmChainProcessor::process() {
	if (chain == nullptr)
		throw std::invalid_argument("A chain was not found to be processed.");

	if (Configuration::isDebugEnabled)
		std::cout << this->chain->getChainDescription();

	int readCount{0};
	int successCount{0};

	for (const auto& entry : std::filesystem::directory_iterator("image")) {
		if (entry.path().extension() != ".png")
			continue;

		std::string fileName{ entry.path().stem().u8string() };
		std::unique_ptr<ImageResolutionQuery> imageQuery{ std::make_unique<ImageResolutionQuery>(fileName) };
		chain->process(*imageQuery);

		if (imageQuery->captchaSolution == imageQuery->captchaProposedSolution)
			successCount++;
		readCount++;
	}

	// Compute success rate, chain info and return results
	double successRate{ (successCount * 100.0) / readCount };
	std::string chainDescription{ this->chain->getChainDescription() };
	return std::make_unique<ChainProcessingResult>(successRate, chainDescription);
}