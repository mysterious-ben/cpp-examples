#include "rxcpp/rx.hpp"
#include <iostream>
#include <list>
#include <time.h>

using namespace std;

const int N = 50000;
const int AVG_WINDOW = 100;

int main()
{
    auto values = rxcpp::observable<>::range(1, N)
                      .window(AVG_WINDOW, 1)
                      .flat_map([](rxcpp::observable<int> w) { return w.average(); });
    clock_t tStart = clock();
    list<float> ma;
    values.subscribe(
        [&ma](float v) { ma.push_back(v); },
        [](exception_ptr ep){
            try {rethrow_exception(ep);}
            catch (const exception& ex) {
                printf("OnError: %s\n", ex.what());
            }
        }
    );
    cout << "Time taken: %.2fs\n" << (double)(clock() - tStart)/CLOCKS_PER_SEC;
    cout << ma.back() << "\n";
}
