#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class DirectMappedCache {
private:
    int cacheSize;
    vector<int> cache;

public:
    DirectMappedCache(int size) : cacheSize(size) {}

    void processStream(int dataSize, const vector<int>& data) {
        int cacheHits = 0;
        int cacheMisses = 0;

        for(int j=0;j<cacheSize;j++){
            cache.push_back(-1);
        }
        for (int i = 0; i < dataSize; ++i) {
            int address = data[i];
            //cout<<address;
            int hit=0;
            for(int j=0;j<cacheSize;j++){
                if(address==cache[j]){
                    hit=1;
                }
            }
            if (hit) {
                //cout<<" hit\n";
                cacheHits++;
            } else {
                
                //cout<<" miss\n";
                cacheMisses++;
                cache[i % cacheSize] = address;
            }
        }

        //cout << "Cache Hits: " << cacheHits << endl;
        cout << "Total Cache Misses:" << cacheMisses << endl;
    }
};

int main() {
    int cacheSize, dataSize;
    
    
    cin >> cacheSize >> dataSize;

   
    vector<int> data(dataSize);
    for (int i = 0; i < dataSize; ++i) {
        cin >> data[i];
    }

   
    DirectMappedCache cache(cacheSize);

    
    cache.processStream(dataSize, data);

    return 0;
}
