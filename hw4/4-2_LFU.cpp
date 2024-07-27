#include <iostream>
#include <vector>
#include <list>

using namespace std;

class LRUCache {
private:
    int cacheSize;
    int setSize;
    vector<vector<int>> cache;
    vector<vector<int>>index;
    vector<vector<int>>freq;

public:
    LRUCache(int size,int setSize) : cacheSize(size), setSize(setSize) {}

    void processStream(int dataSize, const vector<int>& data) {
        int cacheHits = 0;
        int cacheMisses = 0;
        int setNumber=cacheSize/setSize;

        for(int j=0;j<setNumber;j++){
            vector<int> temp;
            cache.push_back(temp);
            freq.push_back(temp);
            index.push_back(temp);
            for(int k=0;k<setSize;k++){
                cache[j].push_back(-1);
                freq[j].push_back(-1);
                index[j].push_back(-1);

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
                        freq[temp][same]++;
                        index[temp][same]=i;
                        break;
                    }
                }

            }
            if (hit) {
                //cout<<address<<" hit\n";
                cacheHits++;
            } else {
                
                //cout<<address<<" miss\n";
                int min_freq=freq[thisSet][0];
                int min=0,min_index=index[thisSet][0];
                for(int j=1;j<setSize;j++){
                    if(freq[thisSet][j]<min_freq){
                        min_freq=freq[thisSet][j];
                        min=j;
                        min_index= index[thisSet][j];
                    }/*else if(freq[thisSet][j]==min_freq){
                        if(index[thisSet][j]>min_index){
                            min_freq=freq[thisSet][j];
                            min=j;
                            min_index= index[thisSet][j];
                        }
                    }*/

                }
                cacheMisses++;
                //cout<<address<<" miss "<<cache[thisSet][min]<<endl;
                cache[thisSet][min] = address;
                freq[thisSet][min]=1;
                index[thisSet][min]=i;
                
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
