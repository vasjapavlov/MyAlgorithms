#include <cmath>
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

//sort order is important
#define LEFT_EDGE 0
#define SPOMENIK 1
#define RIGHT_EDGE 2

struct spomenik {
    int x,y,v;
    spomenik(){}
    spomenik(int _x, int _y, int _v) {x=_x; y=_y; v=_v;}
};

struct rect {
    int x1,x2,y1,y2;
    rect(){}
    rect(int _x1, int _x2, int _y1, int _y2) {
        x1 = _x1; x2 = _x2; y1 = _y1; y2 = _y2;
    }
};

struct event {
    int type; //SPOMENIK/LEFT_EDGE/RIGHT_EDGE
    int x,y,v;
    int y1,y2;
    int idx;
};

bool operator <(const event &a, const event &b) {
    if(a.x == b.x) {
        return a.type < b.type;
    }
    return a.x < b.x;
}

int n, q;
spomenik spomenici[100001];
rect queries[30001];


void input() {
   // ifstream cin("input.txt");
    int a,b,c,d;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a >> b >> c;
        spomenici[i] = spomenik(a, b, c);
    }
    
    cin >> q;
    
    for(int i = 0; i < q; i++) {
        cin >> a >> b >> c >> d;
        queries[i] = rect(a,c,b,d);
    }
}

void compressVertically() {
    set<int> yCoordinates;
    //get all unique y coordinates
    for(int i = 0; i < n; i++) {
        yCoordinates.insert(spomenici[i].y);
    }
    for(int i = 0; i < q; i++) {
        yCoordinates.insert(queries[i].y1);
        yCoordinates.insert(queries[i].y2);
    }
    
    map<int,int> compressedValue;
    
    int nextValue = 0;
    
    //"compress" them
    //start from the lowest y coordinate and move to the highest
    for(set<int>::iterator it = yCoordinates.begin(); it!= yCoordinates.end(); it++) {
        int yValue = *it;
        if(compressedValue.find(yValue) == compressedValue.end()) {
            compressedValue[yValue] = nextValue;
            nextValue++;
        }
    }
    
    //change original to compressed y values
    for(int i = 0; i < n; i++) {
        spomenici[i].y = compressedValue[spomenici[i].y];
    }
    for(int i = 0; i < q; i++) {
        queries[i].y1 = compressedValue[queries[i].y1];
        queries[i].y2 = compressedValue[queries[i].y2];
    }
}

vector<event> events;

void createEvents() {
    for(int i = 0; i < n; i++) {
        event tmp;
        tmp.type = SPOMENIK;
        tmp.x = spomenici[i].x;
        tmp.y = spomenici[i].y;
        tmp.v = spomenici[i].v;
        events.push_back(tmp);
    }
    
    for(int i = 0; i < q; i++) {
        event leftEdge;
        leftEdge.type = LEFT_EDGE;
        leftEdge.idx = i;
        leftEdge.x = queries[i].x1;
        leftEdge.y1 = queries[i].y1;
        leftEdge.y2 = queries[i].y2;
        events.push_back(leftEdge);
        
        event rightEdge;
        rightEdge.type = RIGHT_EDGE;
        rightEdge.idx = i;
        rightEdge.x = queries[i].x2;
        rightEdge.y1 = queries[i].y1;
        rightEdge.y2 = queries[i].y2;
        events.push_back(rightEdge);
    }
    
    sort(events.begin(), events.end());
}

int tree[4000001];

void update(int node,int i,int j,int pos, int val)
{
    if(pos<i || pos>j) return;
    
    if(i==j && pos==i) //&& pos==i
    {
        tree[node] += val;
        return;
    }
    
    update(node<<1,i,(i+j)>>1,pos, val);
    update((node<<1)+1,((i+j)>>1)+1,j,pos, val);
    
    tree[node]=tree[node<<1]+tree[(node<<1)+1];
    
}

#define MAX_TREE_VAL 1000000

int query(int node,int x,int y,int i,int j)
{
    if(y<i || x>j) return 0;
    
    if(x>=i && y<=j) return tree[node];
    
    return query(node<<1,x,(x+y)>>1,i,j) + query((node<<1)+1,((x+y)>>1)+1,y,i,j);
}

void sweep() {
    int results[1000000] = {0};
    int sumBeforeLeftEdge[1000000] = {0};
    
    int E = (int)events.size();
    
    for(int i = 0; i < E; i++) {
        event tmp = events[i];
        if(tmp.type == SPOMENIK) {
            update(1, 0, MAX_TREE_VAL, tmp.y, tmp.v);
        }
        
        if(tmp.type == LEFT_EDGE) {
            sumBeforeLeftEdge[tmp.idx] = query(1, 0, MAX_TREE_VAL, tmp.y1, tmp.y2);
        }
        
        if(tmp.type == RIGHT_EDGE) {
            int res = query(1, 0, MAX_TREE_VAL, tmp.y1, tmp.y2) - sumBeforeLeftEdge[tmp.idx];
            results[tmp.idx] = res;
        }
    }
    
    for(int i = 0; i < q; i++) {
        cout << results[i] << endl;
    }
}

void solve() {
    compressVertically();
    createEvents();
    sweep();
}

int main() {

    input();
    
    solve();
    
    return 0;
}
