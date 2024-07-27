#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include<mutex>
#include <condition_variable>

using namespace std;

const int MAX_THREADS = 4;

int n, global_count = 0;
vector<thread> threads;
mutex mtx;
condition_variable cv;

bool is_prime(int num) {
    if (num == 1) return false;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void count_primes(int start, int end) {
    int local_count=0;
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            local_count++;
        }
    }
    lock_guard<mutex> lock(mtx);
    global_count += local_count;
    cv.notify_one();
}

int main(int argc, char* argv[]) {
    
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " -t [thread_count]" << endl;
        return 1;
    }

    if (string(argv[1]) != "-t") {
        cout << "Usage: " << argv[0] << " -t [thread_count]" << endl;
        return 1;
    }

    int thread_count = min(MAX_THREADS, atoi(argv[2]));//str轉成int
    
    cin >> n;

    
    int chunk_size = n / thread_count;
    int start = 1;

    for (int i = 0; i < thread_count - 1; i++) {
        int end = start + chunk_size - 1;
        threads.emplace_back(thread(count_primes, start, end));
        start = end + 1;
    }

    threads.emplace_back(thread(count_primes, start, n));

    for (auto& t : threads) {
        t.join();
    }

    cout << global_count << endl;
    return 0;
}
