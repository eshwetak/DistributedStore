#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


template <typename T>
class DistributedStore 
{public:
  vector<unordered_map<string, T>> stores;
  T NotFound;

  DistributedStore(): stores(10) {};

  int findStore(string key) {
    if (key.size() == 0) return 0;
    
    char c = key[0];
    return int(c)%10;
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
  DistributedStore<int> d;
  // Write test
  d.write("apple", 20);
  d.write("ornage", 8);
  // d.dump();
  cout<<d.read("apple")<<endl;
  cout<<d.read("temyh")<<endl;
  return 0;
}