#include <list>
#include "Configuration.hpp"
#include "ChainProcessingResult.hpp"

ChainProcessingResult::ChainProcessingResult(double resultPercentage, std::string chainDescription)
	:resultPercentage{ resultPercentage }, chainDescription{ chainDescription } {

}

void ChainProcessingResult::printResult(const std::list<std::unique_ptr<ChainProcessingResult>>& resultList) {
	int iterateAmount{ std::min(Configuration::maxPrintAmount, static_cast<int>(resultList.size())) };

	int i = 0;
	for (const auto& result : resultList) {
		if (i == iterateAmount)
			break;

		std::cout << result->chainDescription;
	}
}