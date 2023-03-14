#ifndef CHAIN_PROCESSING_RESULT_HPP
#define CHAIN_PROCESSING_RESULT_HPP

#include <memory>
#include <string>

class ChainProcessingResult
{
	public:
		ChainProcessingResult(double resultPercentage, std::string chainDescription);
		static void printResult(const std::list<std::unique_ptr<ChainProcessingResult>>& resultList);
		double resultPercentage;
		std::string chainDescription;

		static bool resultOrderComparator(const std::unique_ptr<ChainProcessingResult>& a, const std::unique_ptr<ChainProcessingResult>& b) {
			return a->resultPercentage < b->resultPercentage;
		}
};

#endif


