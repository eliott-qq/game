# Team Members 👨🏼‍💻👩🏻‍💻

- Buenaventura Irish Aves 3036326371
- Chen Xinyu 3036451360
- Kong Deyi 3036279009
- Qi Qingquan 3036291447
- Wu Zeyuan 3035773046

# Description 🎆

Welcome to our text-based Memory Game written in C++

The Memory Game is a cognitive challenge designed to test and enhance memory retention skills. Players are tasked with locating matching pairs of fruits from an array, requiring concentration and recall abilities. It is suitable for participants of all ages and promotes focus, strategy, mental agility, and–of course–enjoyment. 

All pairs of fruits are initially covered and shuffled thoroughly, where each matching pair is distributed randomly. Players can start by ‘flipping’ a pair; if the fruits match, a point is given. If not, the player must remember the location of the fruits as they will be covered again. The game is not simply just a test of lucky guesses–rather of logical reasoning. Developed with various difficulty levels, each with their own countdowns, the objective of the game is to identify all pairs of fruits as quickly as possible. *Even better?!* Players also have the ability to customize their gameplay with the *‘custom function.’*

With endless possible combinations, can you remember it all?

# Features Implemented:

### Generation of random events 🍉🍒🍌
  - The Memory Game generates random pairs of fruits using the Fisher-Yates Shuffle, a well-established algorithm for creating  permutations of a list. By using the current time as a seed, the algorithm ensures that each execution of the program produces a different order for the memory pool, enhancing the game's randomness and replayability.
Data structures for storing data 
 - As the game involves a process of trial and error in testing memorial abilities, the code stores data regarding gameplay. In particular, the number of attempts, correctly identified pairs, and gameplay duration. Moreover, the program includes vectors to store coordinates and memory pairs.

### Dynamic memory management 🤔💭
  - The game utilizes a linked list to store the gameplay records. The game is sorted based on difficulty level then by gameplay duration, allowing players to view their highscores and past trials.
    
### File input/output (e.g., for loading/saving data) 🎁📥📭
  - Individual game progress can be saved and stored in a separate file ‘game_save.txt’, where the program can read past gameplays or allow users to pause and save the current game. Moreover, the linked list is connected to a file where the game records can be saved or deleted when requested.
    
### Program codes in multiple files 📂📃
  - Each section of the game was coded in separate files for easy code manipulation. In particular, the game was split into the main, game, utilities, record, and fruit pool section. *For more information please refer to the developer’s section.*
    
### Multiple Difficulty Levels ▶️🤯
  - The game features three difficulty levels—easy, medium, and hard—each with varying memory pool sizes and corresponding countdown timers. This design allows players to choose to challenge their abilities. Moreover, a custom mode was added for players to challenge their abilities beyond what the game already offers.

### Extra Features: 🤩👀
  - Colored text display for enhanced visual display.

# Developer
*For a more detailed understanding of the multiple files present in the program.*

### Main.cpp
(Attach direct link here)
- The main body of the program begins with an engaging introduction to the game. It then prompts the user to choose between starting a new game or continuing a saved one.
- If the player opts to continue a saved game, the program checks for the existence of a saved file. If a valid save is found, the game will load and display the saved state. If no save exists, the program will inform the player of the invalid choice.
- Should the player choose to start a new game, a fresh and randomized gameplay experience will be generated.

### Fruitpool.cpp
(Attach direct link here)
- The file contains all the possible types of fruits based on text, each with colors represented by ANSI escape codes. 


### Utils.cpp
(Attach direct link here)
- The utilities file contains all the functions involved in the game.
  ### Game Board Generation
    - The function generates and displays the game board for a fruit-matching game. It first determines the maximum length of the fruit names in the fruitnames vector to set an appropriate block width for display, adding padding for centering. It then prints the column numbers, ensuring each number is centered within its block. After drawing a separator line, the function iterates through each row and column of the board, checking if each card has been revealed. If revealed, it displays the corresponding fruit with color formatting; if not revealed, it shows an asterisk. The function calculates padding dynamically based on the actual content length, excluding color codes, to ensure proper alignment. Finally, it prints a closing separator line, completing the visual representation of the game board.
  
  ### Save Game Function
  - The file *‘game_saved.txt’* is where the current gameplay process will be recorded. It begins by opening the file for writing and checks for errors. The function then writes the board dimensions, time limit, number of pairs found, total pairs, and elapsed time. It iterates through the game board to record the indices of the fruits in the fruit pool, followed by the revealed status of each card (1 for revealed, 0 for hidden). It also saves the deck size and the indices of the cards in the fruit pool, along with the size and names of the fruits. Additionally, it captures the state of whether the first card has been flipped and its coordinates if applicable. Finally, the function closes the file and confirms that the game has been successfully saved.
    
 ### Load Game Function
  - The function depends on the *4.Initializing Saved Game* process, which checks the required inputs by opening the file ‘game_save.txt’ If the file is empty, the function returns an invalid input message. If the file contains data, all necessary variables are initialized to match the saved game conditions. This includes generating the board, fruit pairs, and deck as per the saved state. The time limit is adjusted to reflect the saved condition, deducting the time already used. Once all these processes are complete, the file is closed.
    
 ### Initializing Saved Game
  - The file ‘game_save.txt’ is opened to reveal the saved board, revealed fruits, deck, fruit pool, rows, columns, time limit, pairs found, total pairs, elapsed time, whether a card was revealed, and what the card is. All the following variables are then sent to *3.Load Game Function* for proper initializing.
    
 ### Save Game or Quit Game Option
  - The function is triggered after each pair of fruits is found or not found. It prompts the user to input the desired row and column to continue gameplay, save their progress (S), or quit (Q).
  - Upon receiving a row or column input, the function checks if the values are within the board limits. It then provides feedback, either revealing a fruit or indicating an invalid choice.
  - If the user selects S, the output is directed to the 2.Save Game Function. If Q is chosen, the game will end.

 ### Difficulty Level Selection
  - The function begins by presenting the available difficulty options: Easy (E), Medium (M), Hard (H), and Custom (C). The user is then prompted to input their choice. 
  - If the selection is one of E, M, or H, the function forwards the input to the 1.Game Board Generation, where predefined criteria are applied. If the user selects C for Custom, the function will request input for the desired number of rows, columns, and time limit, which will then be sent to *1.Game Board Generation* for processing.

 ### Fisher-Yates Shuffle Algorithm
  - The function starts by initializing the random number generator based on the current time. It then iterates backward through the vector, which represents the board game size, starting from the last element down to the second element. For each element at index i, it generates a random index j between 0 and i. The fruits at indices i and j are then swapped. The output moves to *1.Game Board Generation.*
