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

counting_semaphore<10> sem_a{0};
counting_semaphore<10> sem_b{0};
counting_semaphore<10> sem_d{0};
counting_semaphore<10> sem_e{0};
counting_semaphore<10> sem_i{0};

void f(char name, int index) 
{
    osyncstream(cout) << "Action " << index << " from set " << name << " executed.\n";
   this_thread::sleep_for(chrono::milliseconds(10)); 
}

void run_action_set(char name, int count) 
{
    for (int k = 1; k <= count; ++k) 
    {
        f(name, k);
    }
}

void worker1() 
{
    run_action_set('a', count_a);
    sem_a.release(); 
    
    run_action_set('d', count_d);
    sem_d.release(); 
    sem_d.release(); 
}

void worker2() 
{
    run_action_set('b', count_b);
    sem_b.release(); 
    
    sem_a.acquire(); 
    run_action_set('e', count_e);
    sem_e.release(); 
}

void worker3() 
{
    run_action_set('c', count_c);
    sem_b.acquire(); 
    run_action_set('f', count_f);
    
    sem_e.acquire();
    run_action_set('i', count_i);
    sem_i.release(); 
}

void worker4() 
{
    sem_d.acquire(); 
    run_action_set('h', count_h);
    
    sem_i.acquire();
    run_action_set('k', count_k);
}

void worker5() 
{
    sem_d.acquire(); 
    run_action_set('g', count_g);
    run_action_set('j', count_j);
}

int main() 
{
    cout << "Calculation started." << endl;

   vector<thread> threads;
    
    threads.emplace_back(worker1);
    threads.emplace_back(worker2);
    threads.emplace_back(worker3);
    threads.emplace_back(worker4);
    threads.emplace_back(worker5);

    for (auto& t : threads) 
    {
        if (t.joinable()) 
        {
            t.join();
        }
    }

   cout << "Calculation finished." << endl;
    return 0;
}
