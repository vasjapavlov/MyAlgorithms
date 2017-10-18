#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;


struct state {
    char mat[3][3];
    bool bobsTurn;
    int moveNum;
    
    vector< pair<int,int> > myMoves;
};


//-1 means we win
// 0 means nobody has won yet
// 1 means Bob wins

int whoWins(state x) {
    
    //check all rows
    for(int i = 0; i < 3; i++) {
        int countX = 0;
        int countO = 0;
        for(int j = 0; j < 3; j++) {
            if(x.mat[i][j] == 'x') countX++;
            if(x.mat[i][j] == 'o') countO++;
        }
        
        if(countX == 3) return 1;
        if(countO == 3) return -1;
    }
    
    //check all columns
    for(int j = 0; j < 3; j++) {
        int countX = 0;
        int countO = 0;
        for(int i = 0; i < 3; i++) {
            if(x.mat[i][j] == 'x') countX++;
            if(x.mat[i][j] == 'o') countO++;
        }
        
        if(countX == 3) return 1;
        if(countO == 3) return -1;
    }
    
    
    //check primary and secondary diagonals
    int countPrimaryDiagX = 0, countSecondaryDiagX = 0;
    int countPrimaryDiagO = 0, countSecondaryDiagO = 0;
    
    for(int i = 0; i < 3; i++) {
        if(x.mat[i][i] == 'x') countPrimaryDiagX++;
        if(x.mat[i][i] == 'o') countPrimaryDiagO++;
        
        if(x.mat[i][2-i] == 'x') countSecondaryDiagX++;
        if(x.mat[i][2-i] == 'o') countSecondaryDiagO++;
        
    }
    
    if(countPrimaryDiagX == 3 || countSecondaryDiagX == 3) return 1;
    if(countPrimaryDiagO == 3 || countSecondaryDiagO == 3) return -1;

    
    return 0;
}


int main(int argc, const char * argv[]) {
    
    ifstream cin("input.txt");
    
    int bobRow[9], bobCol[9];
    
    for(int i = 0; i < 9; i++) {
        cin >> bobRow[i] >> bobCol[i];
        bobRow[i]--;
        bobCol[i]--;
    }
    
    
    
    queue<state> q;
    
    state initial;
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            initial.mat[i][j] = '.';
        }
    }
    
    initial.moveNum = 0;
    initial.bobsTurn = true;
    
    
    q.push(initial);
    
    while(!q.empty()) {
        state tmp = q.front();
        q.pop();
        

        int winner = whoWins(tmp);
        
        if(winner == -1) {
            continue;
        }
        
        if(winner == 1) {
            for(int i = 0; i < (int)tmp.myMoves.size(); i++) {
                cout << tmp.myMoves[i].first + 1 << " " << tmp.myMoves[i].second + 1<< endl;
            }
            break;
        }
        
        
        if(tmp.bobsTurn) {
            int lastMove = tmp.moveNum;
            bool moveFound = false;
            for(int i = lastMove; i < 9 && !moveFound; i++) {
                int r = bobRow[i];
                int c = bobCol[i];
                
                if(tmp.mat[r][c] == '.') {
                    tmp.mat[r][c] = 'x';
                    tmp.moveNum = i+1;
                    tmp.bobsTurn = false;
                    moveFound = true;
                    q.push(tmp);
                }
            }
        } else { //this means it's our move
            
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(tmp.mat[i][j] != '.') {
                        continue;
                    }
                    
                    state newState = tmp;
                    
                    newState.mat[i][j] = 'o';
                    newState.bobsTurn = true;
                    newState.myMoves.push_back(make_pair(i, j));
                    q.push(newState);
                }
            }
        }
        
        
    }
    
    return 0;
}





