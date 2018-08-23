//
//  astar.hpp
//  pathfinding
//
//  Created by Marcelo Morais on 2018-08-16.
//  Copyright © 2018 Marcelo Morais. All rights reserved.
//

#ifndef astar_hpp
#define astar_hpp

#define ERR_NO_PATH -1
#define ERR_SMALL_BUFFER -1

//#define ERR_INVALID_PARAM -1

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);

#endif /* astar_hpp */
