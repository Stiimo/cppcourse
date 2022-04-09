#include "threadsafeheap.h"

int main() {
    std::vector<int> v{4, 3, 6, 7, 1, 0, 3};
    ThreadSafeHeap heap(v);
    return 0;
}