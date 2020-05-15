//
//  main.cpp
//  UnionFind
//
//  Created by Vasja Pavlov on 2020-05-15.
//  Copyright © 2020 Vasja Pavlov. All rights reserved.
//

#include <iostream>

using namespace std;

class UnionFind {
    
private:
    
    int id[10000];
    int sz[10000];
    int getRoot(int node) {
        while(id[node] != node) {
            id[node] = id[ id[node] ];
            node = id[node];
        }
        return node;
    }
    
public:
    
    // initializer
    UnionFind(int N) {
        for(int i=0;i<N;i++) {
            id[i]=i;
            sz[i]=1;
        }
    }
    
    bool find(int nodeA, int nodeB) {
        return getRoot(nodeA) == getRoot(nodeB);
    }
    
    void unite(int nodeA,int nodeB) {
        int root1=getRoot(nodeA);
        int root2=getRoot(nodeB);
        
        if(sz[root1] < sz[root2]) {
            id[root1] = root2;
            sz[root2] += sz[root1];
        }
        else {
            id[root2] = root1;
            sz[root1] += sz[root2];
        }
    }
};

int main(int argc, const char * argv[]) {
    
    //    unionFind u(n);
    
    return 0;
}
