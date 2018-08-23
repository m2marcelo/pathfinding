//
//  astar.cpp
//  pathfinding
//
//  Created by Marcelo Morais on 2018-08-16.
//  Copyright © 2018 Marcelo Morais. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

#include "astar.hpp"

using namespace std;

int FindPath( const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize) {
    
//    if ( nStartX < 0 || nStartY < 0 ||
//         nTargetX < 0 || nTargetY < 0 || nOutBufferSize < 0 ||
//         nMapWidth < 1 || nMapHeight < 1 ||
//         nStartX > nMapWidth || nTargetX > nMapWidth ||
//         nStartY > nMapHeight || nTargetY > nMapHeight ||
//         pMap == nullptr || pOutBuffer == nullptr ) {
//        return ERR_INVALID_PARAM;
//    }
    
    // get the matrix position
    auto index = [nMapWidth](int x, int y) {
        return x + (y * nMapWidth);
    };
    
    // manhattan heuristic
    auto heuristic = [=](int u) -> int {
        int x = u % nMapWidth, y = u / nMapWidth;
        return abs(x-nTargetX) + abs(y-nTargetY);
    };
    
    const int nGridSize = nMapWidth*nMapHeight;
    const int UP = -nMapWidth;
    const int DOWN = +nMapWidth;
    const int LEFT = -1;
    const int RIGHT = 1;
    const int nIniPosition = index(nStartX, nStartY);
    const int nEndPosition = index(nTargetX, nTargetY);
    
    int nExplored = 0;
    
    vector<int> pathList(nGridSize), pathLength(nGridSize, INT_MAX);
    
    priority_queue< tuple<int, int, int>,
                    vector<tuple<int, int, int>>,
                    greater<tuple<int, int, int>>> pq;
    
    pathLength[nIniPosition] = 0;
    
    pq.push(make_tuple(0 + heuristic(nIniPosition), 0, nIniPosition));
    int nNextNode = 0;

    while (!pq.empty()) {
        int nCurrentNode = get<2>(pq.top());
        pq.pop();
        for (auto direction : {RIGHT, LEFT, DOWN, UP}) {
            nNextNode = nCurrentNode + direction;
            
            if ((direction == RIGHT && (nNextNode % nMapWidth == 0)) || (direction == LEFT && (nCurrentNode % nMapWidth == 0)))
                continue;
            
            if (0 <= nNextNode && nNextNode < nGridSize && pathLength[nNextNode] > pathLength[nCurrentNode] + 1 && pMap[nNextNode]) {
                pathList[nNextNode] = nCurrentNode;
                pathLength[nNextNode] = pathLength[nCurrentNode] + 1;

                if (nNextNode == nEndPosition)
                    goto finish;
                pq.push(make_tuple(pathLength[nNextNode] + heuristic(nNextNode), ++nExplored, nNextNode));
            }
        }
    }
finish:
    if (pathLength[nEndPosition] == INT_MAX) {
        return ERR_NO_PATH;
    } else if (pathLength[nEndPosition] > nOutBufferSize) {
        cout << "Out buffer too small, giving up..." << endl;
        return ERR_SMALL_BUFFER;
    } else {
        int nCurrentPosition = nEndPosition;
        for (int i = pathLength[nEndPosition] - 1; i >= 0; i--) {
            pOutBuffer[i] = nCurrentPosition;
            nCurrentPosition = pathList[nCurrentPosition];
        }
    }
    
    return pathLength[nEndPosition];
}

