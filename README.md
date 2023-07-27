#### Controls
- **[Space]** Pause the game
- **[C]** Remove 5 to update rate 
- **[V]** Add 5 to update rate 

#### You can compile with *something like* :
`g++ main.cpp -o gameoflife -lSDL2`

#### You can modify the following things in `parameters.hpp` :
- Percent of alive cells at start of game
- Height and width (in cells) of game
- Cell color
- Frame rate
- Update rate (between how many frames the cells update)