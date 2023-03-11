#include <iostream>
#include "AlgorithmChainBuilder.hpp"

int main()
{
    auto builder{ AlgorithmChainBuilder{} };
    std::unique_ptr<std::set<std::unique_ptr<Algorithm>, AlgorithmCompare>> chainInfo;

    int totalCount = 0;
    do {
        chainInfo = builder.returnNextChain();
        if (chainInfo == nullptr)
            break;

        std::cout << "Debugging ID: " << totalCount << std::endl;
        for(auto& algo : *chainInfo)
        {
            algo->printDebugAlgorithm();
        }
        std::cout << "---------" << std::endl;
        totalCount++;
    } while (true);

    std::cout << "Total Count: " << totalCount << std::endl;
}