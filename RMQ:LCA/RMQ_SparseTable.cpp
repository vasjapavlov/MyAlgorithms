//Sparse table RMQ
//Problem: http://www.spoj.com/problems/RMQSQ/

#include <iostream>
#include <cstring>
#include <fstream>
#include <queue>
#include <string>
#include <list>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>

using namespace std;

#define maxN 100000

//table stores indices of array
int table[maxN][17];

void buildTable(int n, int A[]) {
    for(int i = 0; i < n; i++) {
        table[i][0] = i;
    }
    
    for(int pow2 = 1; pow2 <= 17; pow2 ++) {
        int p = (1<<pow2);
        for(int i = 0; i + p - 1 < n; i++) {
            int pp = pow2 - 1;
            if(A[table[i][pp]] < A[table[i + (1<<pp)][pp]]) {
                table[i][pow2] = table[i][pp];
            } else {
                table[i][pow2] = table[i + (1<<pp)][pp];
            }
        }
    }
}

int queryMinIndex(int I, int J, int A[]) {
    int k = log2(J-I+1);
    if(A[ table[I][k] ] < A [table[J - (1<<k) + 1][k]]) {
        return table[I][k];
    } else {
        return table[J - (1<<k) + 1][k];
    }
}

int main()
{
    
    
    ifstream cin("input.txt");
    
    ios_base::sync_with_stdio(false);

    int n,q;
    int I,J;
    int a[maxN];
    
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    buildTable(n, a);
    
    cin >> q;
    
    while(q--) {
        cin >> I >> J;
        
        cout << a[queryMinIndex(I,J,a)] << endl;
    }
    
    return 0;
}
