#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <sstream>

std::vector<unsigned long long> store(100, -1);

unsigned long long fib(const int& num) {
    if (0 == num) {
        return 0;
    }
    if (1 == num) {
        return 1;
    }
    if (-1 != store[num]) {
        return store[num];
    }
    unsigned long long res = store[num] = fib(num - 2) + fib(num - 1); 
    return res;
}

void fibWrapper(const int& num, std::ostringstream& stream) {
    std::thread::id threadId = std::this_thread::get_id();
    auto start = std::chrono::high_resolution_clock::now();
    stream << "fibo(" << num << ") = " << fib(num) << " id = " << threadId << std::endl;
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    stream << "Elapsed time = " << duration.count() << std::endl;
}   

int main() {
    store[0] = 0;
    store[1] = 1;

    std::ostringstream os1;
    std::ostringstream os2;

    int num1 = 90;
    int num2 = 6;

    std::thread t1(fibWrapper, std::ref(num1),  std::ref(os1));
    std::thread t2(fibWrapper, std::ref(num2), std::ref(os2));
    
    t1.join();
    t2.join();

    std::cout << os1.str() << std::endl;
    std::cout << os2.str() << std::endl;

    return 0;
}