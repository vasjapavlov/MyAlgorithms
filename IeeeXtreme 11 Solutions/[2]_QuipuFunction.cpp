#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

#define maxn 1000001
#define maxRange 100001

vector<int> primes;
long long values[maxRange];
vector<int> factorCount[maxRange];

void sieve() {
    bool isPrime[maxn];
    memset(isPrime, true, sizeof isPrime);
    
    for(int i = 2; i <= maxn; i++) {
        if(!isPrime[i]) continue;
        primes.push_back(i);
        if((long long)i*i > maxn) continue;
        
        for(int j = i*i; j <= maxn; j+= i) {
            isPrime[j] = false;
        }
    }
}

void primeFactorization(long long a, long long b) {
    
    for(int i = 0; i < (int)primes.size(); i++) {
        int p = primes[i];
        long long smallest = a - a % p;
        if(smallest < a) smallest += p;
        
        while(smallest <= b) {
            int idx = (int)(smallest - a);
            if(values[idx] % p == 0) {
                factorCount[idx].push_back(0);
            }
            
            int lastFactorIndex = (int)factorCount[idx].size() - 1;
            while(values[idx] % p == 0) {
                values[idx] /= p;
                factorCount[idx][lastFactorIndex]++;
            }
            
            smallest += p;
        }
    }
    
    for(int i = 0; i <= b-a; i++) {
        if(values[i] > 1) {
            factorCount[i].push_back(1);
        }
    }
}

int main(int argc, const char * argv[]) {
    
   // ifstream cin("input.txt");
    
    int t;
    long long a,b,d;
    
    cin >> t;
    cin >> a >> b;
    
    
    sieve();
    
    for(int i = 0; i <= b-a; i++) {
        values[i] = a + i;
    }
    
    primeFactorization(a,b);
    
    while(t--) {
        cin >> d;
        
        int res = 0;
        
        for(long long i = a; i <= b; i++) {
            int totalDivisors = 1;
            int idx = (int)(i - a);
            for(int j = 0; j < (int)factorCount[idx].size(); j++) {
                totalDivisors *= factorCount[idx][j] + 1;
            }
            
            int badPrimesCount = 0;
            long long tmp = i;
            while(tmp % d == 0) {
                badPrimesCount++;
                tmp /= d;
            }
            
            res += totalDivisors / (badPrimesCount + 1);
            
        }
        
        cout << res << endl;
    }
    
    
    return 0;
}
