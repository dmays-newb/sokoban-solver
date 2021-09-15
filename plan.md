## Sokoban Puzzle

### Init To Dos

* ~~Create Test State(s)~~
* Get more test states from prof.
* Are they passed as **command-line arguments**? ... Probably
* What's the output?

### Notes

- Need to prevent backtracking to previous state
  - Check against last move or last map/state when creating next leafs of frontier
  - Need comparison function - one state vs another: compare blocks and robot not obstructions


#### Step 1: Get incoming state data
- ~~Command-line argument~~
- ~~Print out~~
- ~~Create object from input state~~
- ~~Check for legal moves .. next state~~
- Add another map with a narrow passage
- Create function to compare states
  - Can also be achieved somewhat by seeing if the next state matches it's parent's parent..
  - ~~Either way, I'll need a comparison~~
  - ~~Just need to compare Robot and Blocks~~
- Need to test against goal state!!
- Need plan for creating problem (state map)

#### Step 2: Figure out what data structure to use
- Create test structure

#### Step 3: Create Goal Tester
- Try on test input