//
//  main.cpp
//  UnionFind
//
//  Created by Vasja Pavlov on 2020-05-15.
//  Copyright © 2020 Vasja Pavlov. All rights reserved.
//

#include <iostream>

using namespace std;

class UnionFind
{
private:
    
    int parent[10000];
    int weight[10000];
    int getRoot(int node) {
        while(parent[node] != node) {
            parent[node] = parent[ parent[node] ];
            node = parent[node];
        }
        return node;
    }
    
public:
    
    // initializer
    UnionFind(int N) {
        for(int i=0;i<N;i++) {
            parent[i]=i;
            weight[i]=1;
        }
    }
    
    bool find(int nodeA, int nodeB) {
        return getRoot(nodeA) == getRoot(nodeB);
    }
    
    void unite(int nodeA,int nodeB) {
        int root1=getRoot(nodeA);
        int root2=getRoot(nodeB);
        
        if(weight[root1] < weight[root2]) {
            parent[root1] = root2;
            weight[root2] += weight[root1];
        }
        else {
            parent[root2] = root1;
            weight[root1] += weight[root2];
        }
    }
};

int main(int argc, const char * argv[]) {
    
    //    unionFind u(n);
    
    return 0;
}
