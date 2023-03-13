#include <iostream>
#include "Algorithm.hpp"
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
        std::unique_ptr<ImageResolutionQuery> imageQuery = std::make_unique<ImageResolutionQuery>("image/2KX7.png");
        chain->process(*imageQuery);

        std::cout << "---------" << std::endl;
        totalCount++;
    } while (true);

    std::cout << "Total Count: " << totalCount << std::endl;
}