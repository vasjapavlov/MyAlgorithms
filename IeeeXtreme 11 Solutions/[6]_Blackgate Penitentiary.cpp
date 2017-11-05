#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <set>
#include <cmath>
#include <queue>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct person {
    string name;
    int val;
};

bool operator <(const person &a, const person &b) {
    if(a.val < b.val) return true;
    if(a.val > b.val) return false;
    
    return a.name < b.name;
}

int main(int argc, const char * argv[]) {
    ifstream cin("input.txt");
  
    person ppl[1001];
    
    int n;
    
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> ppl[i].name >> ppl[i].val;
    }
    
    sort(ppl,ppl + n);
    
    int i = 0;
    
    while(i < n) {
        int mn = i+1;
        int mx = i+1;
        
        cout << ppl[i].name;
        while(i+1 < n && ppl[i+1].val == ppl[i].val) {
            i++;
            cout << " " <<ppl[i].name;
            mx++;
        }
        
        cout <<" "<< mn <<" "<< mx<< endl;
        
        i++;
    }
    
    return 0;
}
