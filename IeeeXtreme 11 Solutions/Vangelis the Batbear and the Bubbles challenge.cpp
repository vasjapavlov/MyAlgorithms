#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <set>
#include <cmath>
#include <queue>

using namespace std;

#define maxn 1001

vector<int> graph[maxn];
int color[maxn];
int nodesPerComponent[maxn];
int edgesPerComponent[maxn];
int componentCount;

void clenup() {
    componentCount = 0;
    memset(color, 0, sizeof color);
    memset(nodesPerComponent, 0, sizeof nodesPerComponent);
    memset(edgesPerComponent, 0, sizeof edgesPerComponent);
    for(int i = 0; i < maxn; i++) {
        graph[i].clear();
    }
}

void paintGraph(int n) {
    for(int i = 0; i < n; i++) {
        if(color[i] != 0) continue;
        
        componentCount++;
        color[i] = componentCount;
        queue<int> q;
        
        q.push(i);
        
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            
            for(int j = 0; j < graph[node].size(); j++) {
                int v = graph[node][j];
                
                if(color[v] != 0) continue;
                color[v] = componentCount;
                q.push(v);
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        nodesPerComponent[color[i]]++;
    }
}

int main(int argc, const char * argv[]) {
    
    ifstream cin("input.txt");
    
    
    int t;
    int n,m,a,b;
    
    cin >> t;
    
    while(t--) {
        cin >> n >> m;
        
        clenup();
        bool hasLoop = false;
        
        for(int i = 0; i < m; i++) {
            cin >> a >> b;
            
            if(a == b) {
                hasLoop = true;
            }
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        
        if(hasLoop) {
            cout << 1 << endl;
            continue;
        }
        
        paintGraph(n);
        
        set<pair<int,int>> seen;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < graph[i].size(); j++) {
                int v = graph[i][j];
                if(seen.find(make_pair(i, v))!= seen.end() || seen.find(make_pair(v,i))!= seen.end()) continue;
                seen.insert(make_pair(i, v));
                seen.insert(make_pair(v, i));
                
                int c = color[i];
                edgesPerComponent[c]++;
            }
        }
        
        for(int i = 1; i <= componentCount; i++) {
            if(edgesPerComponent[i] >= nodesPerComponent[i]) hasLoop = true;
        }
        
        if(hasLoop) cout << 1 << endl;
        else cout << 0 << endl;
    }
    
    
    return 0;
}
