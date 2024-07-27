#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>

using namespace std;

void count(int index, sem_t* sem, sem_t* next_sem) {
  static mutex io_mutex;
  int num = 1000000;
  while (num--) {}
   
  sem_wait(sem);
  lock_guard<mutex> lock(io_mutex);
  cout << "I'm thread " << index << ", local count: 1000000\n";
  sem_post(next_sem);
}

int main(void) {
  thread t[100];

  sem_t sem_array[100];
  sem_t main_sem;

  

  for (int i = 0; i < 100; i++) {
    sem_init(&sem_array[i], 0, 0);
  }

  sem_init(&main_sem, 0, 0);

  /*for (int i = 0; i < 100; i++){
    t[i] = thread(count, i);
   
  }*/

  for (int i = 0; i < 99; i++) {
    t[i] = thread(count, i, &sem_array[i], &sem_array[i + 1]);
  }

  t[99] = thread(count, 99, &sem_array[99], &main_sem);

  sem_post(&sem_array[0]);
  
  sem_wait(&main_sem);

  
  for (int i = 0; i < 100; i++){
    t[i].join();
  }

  sem_destroy(&main_sem);
  for (int i = 0; i < 100; i++) {
    sem_destroy(&sem_array[i]);
  }
}
