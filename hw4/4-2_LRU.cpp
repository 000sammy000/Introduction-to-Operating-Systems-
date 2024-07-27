#include <iostream>
#include <vector>
#include <list>

using namespace std;

class LRUCache {
private:
    int cacheSize;
    int setSize;
    vector<vector<int>> cache;
    vector<vector<int>>time;

public:
    LRUCache(int size,int setSize) : cacheSize(size), setSize(setSize) {}

    void processStream(int dataSize, const vector<int>& data) {
        int cacheHits = 0;
        int cacheMisses = 0;
        int setNumber=cacheSize/setSize;

        for(int j=0;j<setNumber;j++){
            vector<int> temp;
            cache.push_back(temp);
            time.push_back(temp);
            for(int k=0;k<setSize;k++){
                cache[j].push_back(-1);
                time[j].push_back(-1);

            }
        }
        for (int i = 0; i < dataSize; ++i) {
            int address = data[i];
            
            int hit=0,same;
            int thisSet=i%setNumber;
            for(int temp=0;temp<setNumber;temp++){
                for(same=0;same<setSize;same++){
                    if(address==cache[temp][same]){
                        hit=1;
                        time[temp][same]=i;
                        break;
                    }
                }

            }
            
            if (hit) {
                //cout<<address<<" hit\n";
                cacheHits++;
            } else {
                
                //cout<<address<<" miss\n";
                int min_time=time[thisSet][0];
                int min=0;
                for(int j=1;j<setSize;j++){
                    if(time[thisSet][j]<min_time){
                        min_time=time[thisSet][j];
                        min=j;
                    }
                }
                cacheMisses++;
                //cout<<address<<" miss "<<cache[thisSet][min]<<endl;
                cache[thisSet][min] = address;
                time[thisSet][min]=i;
                
            }
        }

      
        //cout << "Cache Hits: " << cacheHits << endl;
        cout << "Total Cache Misses:" << cacheMisses << endl;
    }
};

int main() {
    int cacheSize, set,dataSize;
    
   
    cin >> cacheSize >>set>> dataSize;
    

  
    vector<int> data(dataSize);
    for (int i = 0; i < dataSize; ++i) {
        cin >> data[i];
    }


   
    LRUCache cache(cacheSize,set);

  
    cache.processStream(dataSize, data);

    return 0;
}
