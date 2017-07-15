/**
HLD
Problem : https://www.codechef.com/JULY17/problems/PSHTTR
//HLD code taken and modified from: https://blog.anudeep2011.com/heavy-light-decomposition/
 */
 
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
 
using namespace std;
 
int root;
#define N 100100
#define LN 17
 
int result[N];
vector <int> adj[N], indexx[N];
int baseArray[N], ptr;
int chainNo, chainInd[N], chainHead[N], posInBase[N];
int depth[N], pa[LN][N], otherEnd[N], subsize[N];
int st[N*4];
 
/*
 * update_tree:
 * Point update. Update a single element of the segment tree.
 */
inline void update_tree(int cur, int s, int e, int &x, int  &val) {
    if(s > x || e <= x) return;
    if(s == x && s == e-1) {
        st[cur] = val;
        return;
    }
    int c1 = (cur<<1), c2 = c1 | 1, m = (s+e)>>1;
    update_tree(c1, s, m, x, val);
    update_tree(c2, m, e, x, val);
    st[cur] = (st[c1] ^ st[c2]);
}
 
/*
 * query_tree:
 * Given S and E, it will return the maximum value in the range [S,E)
 */
 
inline int query_tree(int cur, int s, int e, int S, int E) {
    if(s >= E || e <= S) {
        return 0;
    }
    if(s >= S && e <= E) {
        return st[cur];
    }
    int c1 = (cur<<1), c2 = c1 | 1, m = (s+e)>>1;
    return query_tree(c1, s, m, S, E) ^ query_tree(c2, m, e, S, E);
}
 
/*
 * query_up:
 * It takes two nodes u and v, condition is that v is an ancestor of u
 * We query the chain in which u is present till chain head, then move to next chain up
 * We do that way till u and v are in the same chain, we query for that part of chain and break
 */
 
inline int query_up(int u, int v) {
    if(depth[u] < depth[v]) {
        swap(u,v);
    }
    if(u == v) return 0; // Trivial
    int uchain, vchain = chainInd[v];
    int ans = 0;
    // uchain and vchain are chain numbers of u and v
    while(1) {
        uchain = chainInd[u];
        if(uchain == vchain) {
            // Both u and v are in the same chain, so we need to query from u to v, update answer and break.
            // We break because we came from u up till v, we are done
            if(u==v) break;
            ans ^= query_tree(1, 0, ptr, posInBase[v]+1, posInBase[u]+1);
            
            // Above is call to segment tree query function
            break;
        }
        ans ^= query_tree(1, 0, ptr, posInBase[chainHead[uchain]], posInBase[u]+1);
        // Above is call to segment tree query function. We do from chainHead of u till u. That is the whole chain from
        // start till head. We then update the answer
        u = chainHead[uchain]; // move u to u's chainHead
        u = pa[0][u]; //Then move to its parent, that means we changed chains
    }
    return ans;
}
 
/*
 * LCA:
 * Takes two nodes u, v and returns Lowest Common Ancestor of u, v
 */
int LCA(int u, int v) {
    if(depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    for(int i=0; i<LN; i++) if( (diff>>i)&1 ) u = pa[i][u];
    if(u == v) return u;
    for(int i=LN-1; i>=0; i--) if(pa[i][u] != pa[i][v]) {
        u = pa[i][u];
        v = pa[i][v];
    }
    return pa[0][u];
}
 
bool hasChanged = false;
int lastU, lastV = -1, lastAns;
 
inline void query(int u, int v, int qNum) {
    /*
     * We have a query from u to v, we break it into two queries, u to LCA(u,v) and LCA(u,v) to v
     */
    int lca = LCA(u, v);
    int ans = query_up(u, lca); // One part of path
    int temp = query_up(v, lca); // another part of path
    ans = (ans ^ temp);
    result[qNum] = ans;
}
 
/*
 * change:
 * We just need to find its position in segment tree and update it
 */
void change(int i, int val) {
    int u = otherEnd[i];
    update_tree(1, 0, ptr, posInBase[u], val);
}
 
/*
 * Actual HL-Decomposition part
 * Initially all entries of chainHead[] are set to -1.
 * So when ever a new chain is started, chain head is correctly assigned.
 * As we add a new node to chain, we will note its position in the baseArray.
 * In the first for loop we find the child node which has maximum sub-tree size.
 * The following if condition is failed for leaf nodes.
 * When the if condition passes, we expand the chain to special child.
 * In the second for loop we recursively call the function on all normal nodes.
 * chainNo++ ensures that we are creating a new chain for each normal child.
 */
void HLD(int curNode, int prev) {
    if(chainHead[chainNo] == -1) {
        chainHead[chainNo] = curNode; // Assign chain head
    }
    chainInd[curNode] = chainNo;
    posInBase[curNode] = ptr; // Position of this node in baseArray which we will use in Segtree
    baseArray[ptr++] = 0;
    
    int sc = -1;
    // Loop to find special child
    for(int i=0; i<adj[curNode].size(); i++) if(adj[curNode][i] != prev) {
        if(sc == -1 || subsize[sc] < subsize[adj[curNode][i]]) {
            sc = adj[curNode][i];
        }
    }
    
    if(sc != -1) {
        // Expand the chain
        HLD(sc, curNode);
    }
    
    for(int i=0; i<adj[curNode].size(); i++) if(adj[curNode][i] != prev) {
        if(sc != adj[curNode][i]) {
            // New chains at each normal node
            chainNo++;
            HLD(adj[curNode][i], curNode);
        }
    }
}
 
/*
 * dfs used to set parent of a node, depth of a node, subtree size of a node
 */
void dfs(int cur, int prev, int _depth=0) {
    pa[0][cur] = prev;
    depth[cur] = _depth;
    subsize[cur] = 1;
    for(int i=0; i<adj[cur].size(); i++)
        if(adj[cur][i] != prev) {
            otherEnd[indexx[cur][i]] = adj[cur][i];
            dfs(adj[cur][i], cur, _depth+1);
            subsize[cur] += subsize[adj[cur][i]];
        }
}
 
struct edgeEvent {
    int u, v, c;
    int edgeNum;
    edgeEvent() {}
    edgeEvent(int _u, int _v, int _c, int _edgeNum) {
        u = _u;
        v = _v;
        c = _c;
        edgeNum = _edgeNum;
    }
};
 
struct queryEvent {
    int u,v,c;
    int qNum;
    
    queryEvent(){}
    queryEvent(int _u, int _v, int _c, int _qNum) {
        u = _u;
        v = _v;
        c = _c;
        qNum = _qNum;
    }
};
 
bool operator <(const edgeEvent &a, const edgeEvent &b) {
    return a.c < b.c;
}
 
bool operator <(const queryEvent &a, const queryEvent &b) {
    return a.c < b.c;
}
 
edgeEvent edges[N];
queryEvent queries[N];
 
int nEdges;
int nQueries;
 
#define getcx getchar_unlocked
inline void inp( int &n )//fast input function
{
    n=0;
    int ch=getcx();int sign=1;
    while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getcx();}
    
    while(  ch >= '0' && ch <= '9' )
        n = (n<<3)+(n<<1) + ch-'0', ch=getcx();
    n=n*sign;
}
 
int main() {
    srand(time(NULL));
    root =
    ios_base::sync_with_stdio(false);
//    ifstream cin("vlez.txt");
    
    int t;
    int u,v,c,k;
    inp(t);
    while(t--) {
        nEdges = nQueries = 0;
        ptr = 0;
        int n;
        inp(n);
        root = rand()%n;
        // Cleaning step, new test case
        for(int i=0; i<n; i++) {
            adj[i].clear();
            indexx[i].clear();
            chainHead[i] = -1;
            for(int j=0; j<LN; j++) pa[j][i] = -1;
        }
        memset(st, 0, sizeof(st));
        
        for(int i=1; i<n; i++) {
            inp(u);
            inp(v);
            inp(c);
            u--; v--;
            
            edges[nEdges++] = edgeEvent(u, v, c, i-1);
            adj[u].push_back(v);
            indexx[u].push_back(i-1);
            adj[v].push_back(u);
            indexx[v].push_back(i-1);
        }
        
        
        
        chainNo = 0;
        dfs(root, -1); // We set up subsize, depth and parent for each node
        HLD(root, -1); // We decomposed the tree and created baseArray        
        
        // Below Dynamic programming code is for LCA.
        for(int i=1; i<LN; i++)
            for(int j=0; j<n; j++)
                if(pa[i-1][j] != -1)
                    pa[i][j] = pa[i-1][pa[i-1][j]];
        
        int m;
        inp(m);
        
        for(int i = 0; i < m; i++) {
            inp(u);
            inp(v);
            inp(k);
            u--; v--;
            queries[nQueries++] = queryEvent(u, v, k, i);
        }
        
        edges[nEdges] = edgeEvent(0, 0, 2000000000, 1000000000);
        queries[nQueries] = queryEvent(0, 0, 2000000000, 1000000000);
        sort(edges, edges + nEdges);
        sort(queries, queries + nQueries); 
        int eIdx = 0;
        int qIdx = 0;
        
        while(eIdx < nEdges || qIdx < nQueries) {
            if(edges[eIdx].c <= queries[qIdx].c) {
                change(edges[eIdx].edgeNum, edges[eIdx].c);
                eIdx++;
            } else {
                query(queries[qIdx].u, queries[qIdx].v, queries[qIdx].qNum);
                qIdx++;
            }
        }
        
        for(int i = 0; i < m; i++) {
            cout << result[i] << endl;
        }
    }
} 
