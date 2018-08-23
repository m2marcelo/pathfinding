# path-finding

Finding the path from one point to another into a 2-d grid.
Implement the algorithm with this API in C++

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);

## Implemented solution

The implementation was based in A star solution with tiebraking when we have to choose between paths.

## Solution details

0 - Checking the parameters

There is a parameter check on the code, but according to the test explanation, it says that we can safely assume that
everything is ok, so for that reason I left the check commented and will disconsider for now.

1 - Handling the array input

We get an array and we need to handle it as a 2d grid, like a matrix, to be more effective there is a lambda function that will
return the position on a matrix based notation, folowing the specification as a row-major order.

Example:

Array: 

    A = [1, 2, 3, 4, 5, 6, 7, 8, 9]

Converting to a matrix:

        [ 1 2 3 ]
    M = [ 4 5 6 ]
        [ 7 8 9 ]

So, if we want the element e[1][2] in the matrix [3, 3], That would be 6 in the array it is in index 7 when following the formula x + (y * nMapWidth) -> 1 + 2*3 -> 1+6 = 7

2 - Heuristic

For A star solution we need to calculate the heuristic, in our case, I choose the manhattan heuristic and also stored in a
lambda function called heuristic.

3 - Checking how the cursor will move

For this solution, I won't handle as separated lists, such as open lists and closed lists, I will move inside the array, using
the direction approach, creating values for each direction based on the matrix width to check up and down elements and postion
+1 and -1 for right and left direction, as the following example.

Consider this following [3,3] matrix:

        [ 1 2 3 ]
    M = [ 4 5 6 ]
        [ 7 8 9 ]

Considering the current element 5, the up element will be 2, the down element will be 8, left will be 4 and right will be 6.
For left and right is easy to find, just add or remove one for the current position, but for the up we need to get the current
the current position and subtract the width, in this case, 5 is in index 4 in the array and width of the matrix is 3, so the up
position will be the index 1, which is the element 2 in the array, for the down element we add the width to the current position,
in this case position 4 + width 3, wich is index 7, in this case the element 8.

This math is not always valid according to the array, which is good for us in terms os efficiency because we can discard invalid
address during the calculation.

4 - Checking for traversable and impassable paths

In the solution, this will be handled by checking the input array on a selected index, according to the rules, if it is 0, so it
is impassable, if 1 it is traversable, so considering pMap array as input, we can do a simple check like this:
    if(pMap[index])
If the value at this index is 0, this won't be a valid statement, so this path is impassable. I left like this in the code to be
more flexible to test, because it wasn't explained how this will be verified, but I could left to check for the value 1 to be more
explicit too.


5 - How the algorithm works?

The solution begins handling the input and getting the start and end position on a matrix based notation, create two vectors to
store the path, one holds the node info and the other will hold the path info, that will be needed to retrieve the path indexes.
Then we create a priority queue with tuples and with the greater function to decides which path it will goes, acting as a
tiebreaking.
The queue is made by a tuple with the Manhattan heuristic value to the target, how many node we already explored and which node
will be visited next, so we have the loop, at each iteration we will take the top of the queue to determin the current position
and remove the top from the queue, the we will check the next positions to be followed based on the directions and the current
position.
If the position is valid we will store in the queue anither tuple with the cost from that position to the target, an updated
plus one as explored value and the next node from that position, then we return to the beginning of the loop, we do this until we
find the target as the next node, or until the queue is empty.

After that, we will return if we found the path or not, the answer will be -1 if the path wasn't found, or we find the path we
will return the path to the target and also the number of nodes needed to fulfill the path.

The only corner case was if the outbuffer is smaller than the path, in that case it was told to or give up or call the program
again with bigger buffers, but no specific return code for those situations, I decided to return -1 as well for this case.

## Testing

I left only a small sample in main.cpp, for that reason I left the time count in microseconds, for longer paths please change to
milliseconds or greater depending on the size.



