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

int main(int argc, const char * argv[]) {
    ifstream cin("input.txt");
    
    int d;
    int D[] = {1,1,1,1,1};
    
    cin >> d;
    
    for(int i = 0; i < d; i++) {
        cin >> D[i];
    }
    
    int A[D[0]+1][D[1]+1][D[2]+1][D[3]+1][D[4]+1];
    int sum[D[0]+1][D[1]+1][D[2]+1][D[3]+1][D[4]+1];
    memset(sum, 0, sizeof sum);
    
    for(int i = 1; i <= D[0]; i++)
        for(int j = 1; j <= D[1]; j++)
            for(int k = 1; k <= D[2]; k++)
                for(int l = 1; l <= D[3]; l++)
                    for(int m = 1; m <= D[4]; m++)
                        cin >> A[i][j][k][l][m];
    
    
    for(int i = 1; i <= D[0]; i++)
        for(int j = 1; j <= D[1]; j++)
            for(int k = 1; k <= D[2]; k++)
                for(int l = 1; l <= D[3]; l++)
                    for(int m = 1; m <= D[4]; m++) {
                        sum[i][j][k][l][m] = A[i][j][k][l][m];
                        
                        for(int mask = 0; mask < (1<<d); mask++) {
                            int I[] = {i,j,k,l,m};
                            if(mask == 0) continue;
                            for(int f = 0; f < d; f++) {
                                if((mask & (1<<f)) != 0) I[f]--;
                            }
                            int x = __builtin_popcount(mask);
                            if(x % 2 == 1) {
                                sum[i][j][k][l][m] += sum[I[0]][I[1]][I[2]][I[3]][I[4]];
                            }
                            else {
                                sum[i][j][k][l][m] -= sum[I[0]][I[1]][I[2]][I[3]][I[4]];
                            }
                        }
                    }
    
    int q;
    cin >> q;
    while(q--) {
        int lowD[] = {1,1,1,1,1};
        int hiD[] =  {1,1,1,1,1};
        
        for(int i = 0; i < d; i++) {
            cin >> lowD[i];
        }
        
        for(int i = 0; i < d; i++) {
            cin >> hiD[i];
        }
        
        int res = 0;
        
        for(int mask = 0; mask < (1<<d); mask++) {
            int I[] = {hiD[0],hiD[1],hiD[2],hiD[3],hiD[4]};
            
            for(int i = 0; i < d; i++) {
                if((mask&(1<<i)) != 0) {
                    I[i] = lowD[i] - 1;
                }
            }
            
            int x = __builtin_popcount(mask);
            
            if(x % 2 ==  0) {
                res += sum[I[0]][I[1]][I[2]][I[3]][I[4]];
            } else {
                res -= sum[I[0]][I[1]][I[2]][I[3]][I[4]];
            }
        }
        
        cout << res << endl;
    }
    return 0;
}
