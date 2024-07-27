#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int inQueue;

};


int main() {
    int n, m;
    //int mode,time_quantum ;
    cin >> n >> m ;
    vector<int> time_quantum(n);
    vector<int>mode(n);

    for(int i=0;i<n;i++){
        cin >> mode[i] >> time_quantum[i] ;
    }
    
    vector<Process> processes(m);
    

    for (int i = 0; i < m; i++) {
        processes[i].id = i + 1;
        cin >> processes[i].arrival_time;
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    
        vector<queue<int>> queues(n);
        int current_time = 0;
        int completed = 0;
        
        for (int i = 0; i < m; i++) {
            processes[i].inQueue=0; 
        }
        queues[0].push(0);
        processes[0].inQueue=1;
        int next_process=1;
        int emp=1;
        while (completed < m ) {
            emp=1;
            for(int i=0;i<n;i++){
                
                while(processes[next_process].arrival_time<=current_time&&next_process<m){
                    queues[0].push(next_process);
                    next_process++;
                }
                
                if(queues[i].empty()){
                    continue;
                }
                
                int front_process=queues[i].front();
                int shortest=processes[front_process].remaining_time;
                if(processes[front_process].arrival_time>current_time){
                    continue;
                }

                emp=0;
                if(mode[i]==1){
                    queue<int> tempQueue=queues[i];
                    while(!tempQueue.empty()){
                        int j=tempQueue.front();
                        tempQueue.pop();
                        if(processes[j].remaining_time<shortest){
                            front_process=j;
                            shortest=processes[j].remaining_time;
                        }
                    }
                    int lng=queues[i].size();
                    for(int k=0;k<lng;k++){
                        int a=queues[i].front();
                        queues[i].pop();
                        if(a!=front_process){
                            queues[i].push(a);
                        }

                    }
                }else{
                    queues[i].pop();
                }
                
                
                int execute_time;
                if(mode[i]==2){
                    execute_time = min(time_quantum[i], processes[front_process].remaining_time);
    
                }else{
                    execute_time=processes[front_process].remaining_time;
                }
                if(next_process<m&&i!=0){
                    execute_time=min(execute_time,processes[next_process].arrival_time-current_time);
                }
                if(next_process<m&&mode[i]==1){
                    if(processes[next_process].arrival_time+processes[next_process].burst_time-current_time<execute_time)
                        execute_time=processes[next_process].arrival_time-current_time;
                }
                processes[front_process].remaining_time -= execute_time;
                current_time += execute_time;
                
                while(processes[next_process].arrival_time<=current_time&&next_process<m){
                    queues[0].push(next_process);
                    next_process++;
                }
                if (processes[front_process].remaining_time == 0) {
                    completed++;
                    int finish_time = current_time;
                    processes[front_process].turnaround_time = finish_time - processes[front_process].arrival_time;
                    processes[front_process].waiting_time = processes[front_process].turnaround_time - processes[front_process].burst_time;
                }else{
                    int next=min(i+1,n-1);
                    queues[next].push(front_process);
                
                }
                break;
                
                
            }
        
            if(emp){
                current_time++;
            }

         }

    
   

    int total_waiting_time = 0, total_turnaround_time=0;

    for (const Process& p : processes) {
        cout << p.waiting_time << " " << p.turnaround_time << endl;
        total_waiting_time += p.waiting_time;
        total_turnaround_time+=p.turnaround_time;
    }

    cout << total_waiting_time << endl;
    cout << total_turnaround_time << endl;

    return 0;
}
