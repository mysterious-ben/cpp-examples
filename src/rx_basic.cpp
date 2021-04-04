#include "rxcpp/rx.hpp"

int main()
{
    auto ints = rxcpp::observable<>::range(1, 10);
    ints.subscribe([](int v) { printf("OnNext: %d\n", v); });
}