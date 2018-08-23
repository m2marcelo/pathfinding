//
//  main.cpp
//  pathfinding
//
//  Created by Marcelo Morais on 2018-08-16.
//  Copyright © 2018 Marcelo Morais. All rights reserved.
//

#include <iostream>
#include <chrono>

using namespace std;

#include "astar.hpp"

int main() {
    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    int pOutBuffer[12];
    auto start = chrono::steady_clock::now();
    int result = FindPath(0, 0, 2, 2, pMap, 4, 3, pOutBuffer, 12);
    auto end = chrono::steady_clock::now();
    cout << "Elapsed time : " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    cout << "Path size returned = " << result << endl;
    
    for (auto i = 0; i < result; ++i)
        cout << pOutBuffer[i] << ' ';
    
    cout << "" << endl;
    
    return 0;
}


