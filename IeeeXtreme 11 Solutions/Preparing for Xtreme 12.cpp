#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <map>
#include <cmath>
#include <queue>
#include <sstream>

using namespace std;


int dp[2][1<<20];
int main(int argc, const char * argv[]) {
    
    ifstream cin("input.txt");
    
    map<string,int> topicToNumber;
    string s, topicString;
    int time[101];
    int nBooks = 0;
    int nTopics = 0;
    vector<string> topics[101];
    
    
    while(getline(cin,s)) {
        istringstream is(s);
        
        is >> time[nBooks];
        
        while(is>>topicString) {
            if(topicToNumber.find(topicString) == topicToNumber.end()) {
                topicToNumber[topicString] = nTopics++;
            }
            topics[nBooks].push_back(topicString);
        }
        
        nBooks++;
    }
    
    
    memset(dp, 62, sizeof dp);
    
    int prev = 0;
    int cur = 1;
    
    dp[0][0] = 0;
    
    for(int i = 1; i <= nBooks; i++) {
        int curBookMask = 0;
        for(int j = 0; j < (int)topics[i-1].size(); j++) {
            topicString = topics[i-1][j];
            curBookMask |= (1<<topicToNumber[topicString]);
        }
        
        
        for(int j = 0; j < (1<<nTopics); j++) {
            dp[cur][j] = dp[prev][j];
        }
        
        for(int j = 0; j < (1<<nTopics); j++) {
            int newMask = j | curBookMask;
            
            
            dp[cur][newMask] = min(dp[cur][newMask], dp[prev][j] + time[i-1]);
            
        }
        
        prev = 1 - prev;
        cur = 1 - cur;
    }
    
    cout << dp[prev][(1<<nTopics) - 1] << endl;
    return 0;
}
