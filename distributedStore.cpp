#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


template <typename T>
class DistributedStore 
{
  vector<unordered_map<string, T>> stores;
  T NotFound;
  int storesCount;
  
  public:
  DistributedStore(int sct): stores(sct), storesCount(sct) {};

  int findStore(string key) {
    if (key.size() == 0) return 0;
    
    char c = key[0];
    return int(c)%storesCount;
  }

  void write(string key, T val) {
    int loca = findStore(key);

    stores[loca][key] = val;
  }

  T read(string key) {
    int loca = findStore(key);
    auto h = stores[loca].find(key);

    if(h == stores[loca].end()) return NotFound;
    return h->second;
  }

  void dump() {
    for (int i=0; i<stores.size(); i++) {
      cout<<"store "<< i <<endl;
      for (auto x : stores[i])
        cout<< x.first<< " " << x.second<<endl;
      cout<<endl;
    }
  }
};


int main() {
  DistributedStore<int> d(3);
  // Write function
  d.write("apple", 20);
  d.write("ornage", 8);

  // read function
  cout<<d.read("apple")<<endl;
  cout<<d.read("temyh")<<endl;
  cout<<endl;

  // Dump function
  cout<<"display:"<<endl;
  d.dump();
  return 0;
}