#include <iostream>
#include "Algorithm.hpp"
#include "AlgorithmChainBuilder.hpp"
#include "AlgorithmChainProcessor.hpp"
#include "ChainProcessingResult.hpp"

int main()
{
    AlgorithmChainBuilder builder{};
    std::unique_ptr<Algorithm> chain;
    std::list<std::unique_ptr<ChainProcessingResult>> resultList;

    do {
        chain = builder.returnNextChain();
        if (chain == nullptr)
            break;

        AlgorithmChainProcessor processor{std::move(chain)};
        std::unique_ptr<ChainProcessingResult> chainProcessingResult{ processor.process() };
        resultList.push_back(std::move(chainProcessingResult));
    } while (true);

    resultList.sort(ChainProcessingResult::resultOrderComparator);
    ChainProcessingResult::printResult(resultList);
}