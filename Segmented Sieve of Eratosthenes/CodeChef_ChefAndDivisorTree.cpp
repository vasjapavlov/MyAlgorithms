//
//  main.cpp
//  ChefAndDivisorTree
//
//  Created by Vasja Pavlov on 5/4/17.
//  Copyright © 2017 Vasja Pavlov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define maxn 1000010
#define maxRangeDiff 100010
long long value[maxRangeDiff];
vector<int> primes;
vector<long long> factors[maxRangeDiff];
vector<int> factorsCount[maxRangeDiff];

bool isPrime[maxn];

void sieve() {
    memset(isPrime ,true , sizeof(isPrime));
    
    //    long long rootN = sqrt(maxn);
    
    for(int i = 2; i <= 1000000; i++) {
        if(!isPrime[i]) continue;
        primes.push_back(i);
        if((long long)i*i > 1000000) continue;
        for(int j = i*i; j <= 1000000; j += i) {
            isPrime[j] = false;
        }
    }
}

//Find the prime factorization of each number in the range [a..b], with segmented sieve of Erathostenes
void primeFactorization(long long a, long long b) {
    
    long long smallest;
    int curN;
    int idx;
    for(int i = 0; i < primes.size(); i++) {
        int p = primes[i];
        smallest = a - a % p;
        if(smallest < a) {
            smallest += p;
        }
        idx = (int)(smallest - a);
        while(smallest <= b) {
            if(value[idx] % p == 0) {
                factors[idx].push_back(p);
                factorsCount[idx].push_back(1);
                value[idx] /= p;
            }
            curN = (int)factorsCount[idx].size();
            while(value[idx] % p == 0) {
                value[idx] /= p;
                factorsCount[idx][curN - 1]++;
            }
            smallest += p;
            idx = (int)(smallest - a);
        }
    }
}

int main(int argc, const char * argv[]) {
    
    long long a,b;
    
    cin >> a >> b;
    
    
    for(long long i = a; i <= b; i++) {
        value[i-a] = i;
    }
    
    
    sieve();
    primeFactorization(a,b);
    
    long long res = 0;
    
    int idx, nFactors, nDivisors, tmp;
    
    for(long long ii = a; ii <= b; ii++) {
        if(ii == 1) continue;
        idx = (int)(ii - a);
        
        
        if(value[idx] > 1) {
            factors[idx].push_back(value[idx]);
            factorsCount[idx].push_back(1);
        }
        
        nFactors = (int)factors[idx].size();
        
        
        priority_queue<int> q;
        nDivisors = 1;
        for(int i = 0; i < nFactors; i++) {
            nDivisors *= (factorsCount[idx][i]+1);
            q.push(factorsCount[idx][i]);
        }
        
        while(!q.empty()) {
            tmp = q.top();
            q.pop();
            
            //Only 1 has 1 divisor
            if(nDivisors == 1) {res++; break;}
            
            
            res += nDivisors;
            nDivisors /= (tmp+1);
            nDivisors *= tmp;
            q.push(tmp-1);
        }
        res --;
    }
    cout << res << endl;
    return 0;
}
