#include <iostream>
#include "AlgorithmChainBuilder.hpp"

int main()
{
    auto builder{ AlgorithmChainBuilder{} };
    std::unique_ptr<Algorithm> chain;

    int totalCount = 0;
    do {
        chain = builder.returnNextChain();
        if (chain == nullptr)
            break;

        std::cout << "Debugging ID: " << totalCount << std::endl;
        const Algorithm* current = chain.get();
        while (current != nullptr)
        {
            current->printDebugAlgorithm();
            current = (current->successor).get();
        }

        std::cout << "---------" << std::endl;
        totalCount++;
    } while (true);

    std::cout << "Total Count: " << totalCount << std::endl;
}