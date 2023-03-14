#ifndef ALGORITHM_CHAIN_PROCESSOR_HPP
#define ALGORITHM_CHAIN_PROCESSOR_HPP

#include "ChainProcessingResult.hpp"

class AlgorithmChainProcessor
{
	public:
		AlgorithmChainProcessor(std::unique_ptr<Algorithm> chain);
		std::unique_ptr<ChainProcessingResult> process();

	private:
		std::unique_ptr<Algorithm> chain;

};

#endif