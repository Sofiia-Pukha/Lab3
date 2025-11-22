#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <syncstream> 
#include <chrono>     
#include <string>

using namespace std;

const int count_a = 7;
const int count_b = 7;
const int count_c = 6;
const int count_d = 6;
const int count_e = 7;
const int count_f = 4;
const int count_g = 4;
const int count_h = 7;
const int count_i = 4;
const int count_j = 9;
const int count_k = 5;

std::binary_semaphore sem_a{0};
std::binary_semaphore sem_b{0};
std::binary_semaphore sem_c{0};
std::binary_semaphore sem_d{0};
std::binary_semaphore sem_e{0};
std::binary_semaphore sem_f{0};
std::binary_semaphore sem_g{0}; 
std::binary_semaphore sem_h{0}; 
std::binary_semaphore sem_i{0};


void f(char name, int index) 
{
    std::osyncstream(std::cout) << "Action " << index << " from set " << name << " executed.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
}

void run_action_set(char name, int count) 
{
    for (int k = 1; k <= count; ++k) 
    {
        f(name, k);
    }
}
