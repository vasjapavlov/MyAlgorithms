/* Code generated && tested by LizardCode for CodeFu */
#include <limits.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <set>

//Illegal includes:
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class SecretNumbers
{
public:
    
    int toInt(string s) {
        istringstream is(s);
        int x;
        is >> x;
        return x;
    }
    
    int lessThan, areEqual, greaterThan;
    long long count[105][901][3];
    long long sum[105][901][3];
    
    int findSum( string N, int K )
    {
        int n = (int)N.size();
        int mod = 1000000007;
        if(N.size() == 1) {
            int tmp = toInt(N);
            if(K <= tmp) return 1;
            return 0;
        }
        lessThan = 0;
        areEqual = 1;
        greaterThan = 2;
        
        memset(count,0,sizeof(count));
        memset(sum,0,sizeof(sum));
        int d = N[0]-'0';
        for(int i = 1; i <= 9; i++) {
            
            if(i < d) {
                count[0][i][lessThan] = 1;
                sum[0][i][lessThan] = i;
            }
            if(i == d) {
                count[0][i][areEqual] = 1;
                sum[0][i][areEqual] = i;
            }
            if(i > d) {
                count[0][i][greaterThan] = 1;
                sum[0][i][greaterThan] = i;
            }
        }
        
        for(int i = 1; i < n; i++) { //up to i
            d = N[i] - '0';
            for(int k = 0; k <= K; k++) { //having sum k
                
                for(int j = 0; j <= 9; j++) { //ending at digit j
                    if(k-j < 0) continue;
                    
                    count[i][k][lessThan] += count[i-1][k-j][lessThan];
                    count[i][k][lessThan] %=mod;
                    count[i][k][greaterThan] += count[i-1][k-j][greaterThan];
                    count[i][k][greaterThan] %= mod;
                    
                    sum[i][k][lessThan] += sum[i-1][k-j][lessThan]*10;
                    sum[i][k][lessThan] += count[i-1][k-j][lessThan]*j;
                    sum[i][k][lessThan] %= mod;
                    
                    sum[i][k][greaterThan] += sum[i-1][k-j][greaterThan]*10;
                    sum[i][k][greaterThan] += count[i-1][k-j][greaterThan]*j;
                    sum[i][k][greaterThan] %= mod;

                    if(j < d) {
                        count[i][k][lessThan] += count[i-1][k-j][areEqual];
                        count[i][k][lessThan] %= mod;
                        sum[i][k][lessThan] += sum[i-1][k-j][areEqual]*10;
                        sum[i][k][lessThan] += count[i-1][k-j][areEqual]*j;
                        sum[i][k][lessThan] %= mod;
                    }
                    if(j == d) {
                        
                        count[i][k][areEqual] += count[i-1][k-j][areEqual];
                        count[i][k][areEqual] %= mod;
                        sum[i][k][areEqual] += sum[i-1][k-j][areEqual]*10;
                        sum[i][k][areEqual] += count[i-1][k-j][areEqual]*j;
                        sum[i][k][areEqual] %= mod;
                    }
                    if(j > d) {
                        
                        count[i][k][greaterThan] += count[i-1][k-j][areEqual];
                        count[i][k][greaterThan] %= mod;
                        sum[i][k][greaterThan] += sum[i-1][k-j][areEqual]*10;
                        sum[i][k][greaterThan] += count[i-1][k-j][areEqual]*j;
                        sum[i][k][greaterThan] %= mod;
                    }
                }
            }
        }
        
        long long cnt = 0;
        for(int i = 0; i < n-1; i++) {cnt += sum[i][K][lessThan] + sum[i][K][greaterThan] + sum[i][K][areEqual]; cnt%= mod;}
        cnt += sum[n-1][K][lessThan] + sum[n-1][K][areEqual];
        cnt %= mod;
        return (int)cnt;
        
    }
};

const int Test_No=1;

int main()
{
    SecretNumbers tmp;
    int res;
    string N;
    int K;
    /***************************Test 1 ********************************/
    
    if(Test_No==0 || Test_No==1){
        N = "644544161935759630816007181116285010836763019320909742319598445962733743962568925766193472624774323";
        K = 597;
        res = tmp.findSum(N,K);
        if(res == 66) cout<<"test #"<<1<<" Correct!\n\n";
        else {cout<<"test #"<<1<<" Wrong!\n";
            cout<<"Expected: "<<66<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    /***************************Test 2 ********************************/
    
    if(Test_No==0 || Test_No==2){
        N = "100";
        K = 1;
        res = tmp.findSum(N,K);
        if(res == 111) cout<<"test #"<<2<<" Correct!\n\n";
        else {cout<<"test #"<<2<<" Wrong!\n";
            cout<<"Expected: "<<111<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    /***************************Test 3 ********************************/
    
    if(Test_No==0 || Test_No==3){
        N = "127";
        K = 4;
        res = tmp.findSum(N,K);
        if(res == 446) cout<<"test #"<<3<<" Correct!\n\n";
        else {cout<<"test #"<<3<<" Wrong!\n";
            cout<<"Expected: "<<446<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    /***************************Test 4 ********************************/
    
    if(Test_No==0 || Test_No==4){
        N = "723";
        K = 13;
        res = tmp.findSum(N,K);
        if(res == 22790) cout<<"test #"<<4<<" Correct!\n\n";
        else {cout<<"test #"<<4<<" Wrong!\n";
            cout<<"Expected: "<<22790<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    /***************************Test 5 ********************************/
    
    if(Test_No==0 || Test_No==5){
        N = "104";
        K = 2;
        res = tmp.findSum(N,K);
        if(res == 134) cout<<"test #"<<5<<" Correct!\n\n";
        else {cout<<"test #"<<5<<" Wrong!\n";
            cout<<"Expected: "<<134<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    /***************************Test 6 ********************************/
    
    if(Test_No==0 || Test_No==6){
        N = "997";
        K = 22;
        res = tmp.findSum(N,K);
        if(res == 17094) cout<<"test #"<<6<<" Correct!\n\n";
        else {cout<<"test #"<<6<<" Wrong!\n";
            cout<<"Expected: "<<17094<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    /***************************Test 7 ********************************/
    
    if(Test_No==0 || Test_No==7){
        N = "744";
        K = 4;
        res = tmp.findSum(N,K);
        if(res == 2220) cout<<"test #"<<7<<" Correct!\n\n";
        else {cout<<"test #"<<7<<" Wrong!\n";
            cout<<"Expected: "<<2220<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    /***************************Test 8 ********************************/
    
    if(Test_No==0 || Test_No==8){
        N = "605";
        K = 15;
        res = tmp.findSum(N,K);
        if(res == 14085) cout<<"test #"<<8<<" Correct!\n\n";
        else {cout<<"test #"<<8<<" Wrong!\n";
            cout<<"Expected: "<<14085<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    /***************************Test 9 ********************************/
    
    if(Test_No==0 || Test_No==9){
        N = "324";
        K = 8;
        res = tmp.findSum(N,K);
        if(res == 4077) cout<<"test #"<<9<<" Correct!\n\n";
        else {cout<<"test #"<<9<<" Wrong!\n";
            cout<<"Expected: "<<4077<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    /***************************Test 10 ********************************/
    
    if(Test_No==0 || Test_No==10){
        N = "40178114685284207017";
        K = 60;
        res = tmp.findSum(N,K);
        if(res == 577566459) cout<<"test #"<<10<<" Correct!\n\n";
        else {cout<<"test #"<<10<<" Wrong!\n";
            cout<<"Expected: "<<577566459<<"\n";
            cout<<"Recieved: "<< res <<" \n\n";}
        cout<<"---------------------------------------------"<<"\n";
        
    }
    /******************************************************************/
    
    
    return 0;
    
}
