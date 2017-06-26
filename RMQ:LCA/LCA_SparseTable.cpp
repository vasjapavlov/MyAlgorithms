//Sparse table LCA
//O(N*logN) build time and space
//O(logN) query time
//Problem: http://www.spoj.com/problems/LCA/

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

#define maxN 1001
#define maxLog 11
//table stores indices of array
int table[maxN][maxLog];
int parent[maxN];
int level[maxN];
int n;

//nodes are numbered from 1 to n

void buildTable() {
    memset(table, -1, sizeof table);
    
    for(int i = 1; i <= n; i++) {
        table[i][0] = parent[i];
    }
    
    for(int j = 1; j < maxLog; j++) {
        for(int i = 1; i <= n; i++) {
            if(table[i][j-1] != -1) {
                table[i][j] = table[ table[i][j-1] ][j-1];
            }
        }
    }
}

int lca(int u, int v) {
    int log;
    
    if(level[u] < level[v]) {
        swap(u,v);
    }
    
    
    for(log = 1; (1<<log) <= level[u]; log++);
    log--;
    
    
    for(int i = log; i >= 0; i--) {
        if(level[u] - (1<<i) >= level[v]) {
            u = table[u][i];
        }
    }
    
    if(u == v) {
        return u;
    }
    
    for(int i = log; i >= 0; i--) {
        if(table[u][i] != -1 && table[u][i] != table[v][i]) {
            u = table[u][i];
            v = table[v][i];
        }
    }
    
    return parent[u];
}

void calculateNodeLevels(int node, int curLevel, vector<int> children[]) {
    level[node] = curLevel;
    
    for(int i = 0; i < children[node].size(); i++) {
        int c = children[node][i];
        calculateNodeLevels(c, curLevel + 1, children);
    }
}

int main()
{
    
    
//    ifstream cin("input.txt");
    
    ios_base::sync_with_stdio(false);

    int t, m, child, q, u ,v;
    
    cin >> t;
    
    for(int T = 1; T <= t; T++) {
        cin >> n;
        
        memset(parent, -1, sizeof parent);
        vector<int> children[maxN];

        int root = -1;
        
        for(int i = 1; i <= n; i++) {
            cin >> m;
            
            for(int j = 0; j < m; j++) {
                cin >> child;
                parent[child] = i;
                children[i].push_back(child);
                
            }
        }
        
        for(int i = 1; i <= n; i++) {
            if(parent[i] == -1) {
                root = i;
            }
        }
//
        calculateNodeLevels(root, 0, children);
        
        buildTable();
        
        cin >> q;
        
        cout << "Case " << T << ":\n";
        while(q--) {
            cin >> u >> v;
            cout << lca(u, v) << endl;
        }
    }
    return 0;
}
