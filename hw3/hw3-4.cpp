#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

int n, m, thread_count;
vector<uint64_t> subsets;
uint64_t one = static_cast<uint64_t>(1);
atomic<uint64_t> global_count(0);
mutex mtx;
int power=0;
vector<thread> threads;
vector<uint64_t>local_count;

void solveRecursive(int index, uint64_t current,int thread_id) {
    if (index== m) {
        if (current == (one << n) - 1) {
            //lock_guard<mutex> lock(mtx);
            local_count[thread_id]++;
        }
    } else {
        solveRecursive(index + 1, current,thread_id);
        solveRecursive(index + 1, current | subsets[index],thread_id);
    }
}

void solve(int start) {
    uint64_t current = 0;
    int st=start;
    for(int i=0;i<power;i++){
        if(start%2!=0){
            current=current | subsets[i];
        }else{
            current=current;
        }
        start=(start-(start%2))/2;
    }
    local_count.push_back(0);
    threads.emplace_back(solveRecursive,power,current,st);
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

    thread_count = atoi(argv[2]);
    
    cin >> n >> m;

    subsets.resize(m);
    for (int i = 0; i < m; i++) {
        int p, temp;
        cin >> p;
        for (int j = 0; j < p; j++) {
            cin >> temp;
            subsets[i] |= (one << temp);
        }
    }

   
    power=0;
    int temp=thread_count;
    while(temp!=1){
        temp/=2;
        power++;
    }
   

    for (int i = 0; i < thread_count; ++i) {
        //threads.emplace_back(solve, i);
        solve(i);
    }


    for (auto& t : threads) {
        t.join();
    }

    for (uint64_t lc : local_count) {
        global_count += lc;
    }

    cout << global_count << endl;
    return 0;
}