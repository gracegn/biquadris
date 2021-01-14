# Biquadris

Tetris-variation video game expanded for 2-player competition with additional rules, obstacles and strategies involved.

##  To Play

Download, run the following code in your command line terminal in the folder's root directory:
```bash???
make
./biquadris
LOL
```

##  Rules

A game of Biquadris consists of two boards, each 11 columns wide and 15 rows high. Blocks consisting of four cells (tetrominoes) appear at the top of each board, and you must drop them onto their respective boards so as not to leave any gaps. Once an entire row has been filled, it disappears, and the blocks above move down by one unit.

Biquadris differs from Tetris in one significant way: it is not real-time. You have as much time as you want to decide where to place a block. Players will take turns dropping blocks, one at a time. A player’s turn ends when he/she has dropped a block onto the board (unless this triggers a special action; see below). During a player’s turn, the block that the opponent will have to play next is already at the top of the opponent’s board (and if it doesn’t fit, the opponent has lost).



The major components of the system are as follows.

### Blocks

There are seven types of blocks, shown below with their names and initial configurations:

```
              J             L
  IIII        JJJ         LLL

  I-block     J-block     L-block


  OO           SS         ZZ
  OO          SS           ZZ
  
  O-block     S-block     Z-block


  TTT
   T
  
  T-block
```

