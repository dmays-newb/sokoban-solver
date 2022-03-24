# sokoban-solver

## Code Comments

Functions and variables will have comments to describe their purpose unless self-explanatory. I tried to utilize "self-documenting code" to the greatest extent possible. However, I did provide more extensive comments on in the map.cpp file as this is where the majority of the relevant actions take place.

You will notice that several files are quite similar: astar.cpp, bf_search.cpp, greedy_plus.cpp, greedy_search.cpp, df_search.cpp. I kept these similar for the sake of simplicity as I programmed. I am rusty on makefiles, so I created these separate files and the user chooser their prefered search algorithm via a command-line argument. Comments will be fairly minimal on these files. Each includes a constructor which takes the root state from which the search tree is built. Each also includes an expand() function which creates the search tree utilizing a unordered-map closed-list and a queue, stack, or priority-queue frontier.


## Instructions

- This program was built to run on a Linux system.
- You will need gcc installed
- There is one program which utilizes one of the search algorithms depending upon the user's choice.

### Compiling the Program

- Open the folder containing the code and this README file in a Unix system.
- In the terminal, cd into the project's root folder: `sokoban-solver`
- Compile the software using `make` command

### Running the Program

- The choice of search algorithm and input file are provided via command-line arguments
- Running the program from the terminal follows this format: `./sokoban-solver <algorithm-code> <puzzle-file>`
- Acceptable algorithm codes are:
  - Breadth-First Search: bfs
  - Depth-First Search: dfs
  - Greedy Search (Manhattan Distances): greedy
  - Improved Greedy Heuristic Search: greedy_plus
  - A*: astar
- Example:
  - `./sokoban-solver greedy_plus ./test-states/test-state-4`
- The program should output three things:
  - Search algorithm timing in milliseconds
  - Steps to solve the puzzle
  - Total moves to solve the puzzle

## Heuristic Information

The improved heuristic incorporates a corner and wall check for a given state. This is comprised of the function Map::findCornerBlocks() which checks the state for blocks which are stuck in a corner. It rules out situations in which a storage space is in the same corner as the block as this would be an exception that I would not want the heuristic to favor against. This function also accounts for blocks which are pushed against a wall. This situation does not limit movement options to the same extent as a corner block but does generally limit the degrees of movement for a given block. The findCornerBlocks() function returns an integer ranging from 0 to 3. You will notice in lines 385-392 of map.cpp that I have provided a greater weight to corner blocks and that I only consider wall-bound blocks as an impediment if their count is greater than or equal to half of the total count of the blocks. I experimented to a great extent with different weights for corner and wall blocks and found that this heuristic provided the best balance across different puzzles. There are some situations in which this heuristic does not perform as well the generic greedy search, and these often seem to be those with narrow openings to push blocks through. Given more time, I would have refined this heuristic to a greater extent. 

## A* Comment

Please refer to lines 456-458 of map.cpp. I decided to scale my path cost using a square root function and then halving that value relative to the sum of distances from the goal state. Without scaling, my A* algorithm could return a solution equivalent or close to equivalent to the BFS for some puzzles but would take an exceedingly long time to process for most of my puzzles. Others in the class have mentioned similar issues with their A* search. Without weighting the path cost (depth) it very quickly overwhelms the sum of distances to goal state measure with moderate to complex puzzles. I experimented with linear and logarithmic scales for the depth but found `1/2 * sqrt(depth)` to provide the best balance of performance and solution quality over a range of test puzzles. 

## Analysis and Discussion

Please see the attached Excel spreadsheet with performance information for three of my test cases.

During all of my tests (~10), my program was able to find a solution except when utilizing BFS for more complex puzzles. I believe that BFS would have returned a result but I didn't have the patience to wait 30+ minutes for each test. I measured and compared performance for three of my ten test cases, and these provide interesting results that provide some insights into the limitations of my custom heuristic and A* search. The most obvious issues arise with test-state-4. This is a complex puzzle which includes many narrow passages and wall-bound storage spaces, and it greatly challenges my wall-and-corner weighted heuristic. This leads to significantly more time required to produce a solution compared to the greedy (Manhattan Distance) algorithm.

During my testing and heuristic refinements, I also found that there is a performance threshold that a heuristic needs to cross in order to be cost-effective. Some of my earlier attempts at the heuristic did not provide additional performance benefits to outweigh the additional computation that was required for a given state. So I realized that care should be given in how I form my code to process each state efficiently.

I also learned that it's very important to think critically about how I should represent each state in the software while I'm performing my initial planning. I created a position data type to represent each space on a given puzzle. This seemed like a straight-forward solution for representing the spaces on the puzzle, but I realized during lecture that it would have been even simpler to represent each block or robot as a simple integer in an array. This would have allowed for an easier and more computationally efficient heuristic function. Also I may not have needed to program as many member functions to compare and modify positions and states.

