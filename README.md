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

### Data structures for storing data 
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

# Non-standard Libraries 📚
### 1. System Libraries
- Code: #ifndef_WIN32 & #endif
- Function: The code is a preprocessor directive in C/C++ which allows the conditional compilation of code. In multi-platform projects, certain code or libraries may only work on specific operating systems; hence, the code ensures that the codebase is unified with the management of platform-specific functionality.	

### 2. POSIX (Portable Operating System Interface) Libraries
- Code: <unistd.h>
- Functions: The game utilizes the sleep function, where the game is paused for a few seconds to allow the user to view the game pairs.

# Developer 🥸💻
*For a more detailed understanding of the multiple files present in the program.*

## main.cpp
(Attach direct link here)
- The main body of the program begins with an engaging introduction to the game. It then prompts the user to choose between starting a new game or continuing a saved one.
- If the player opts to continue a saved game, the program checks for the existence of a saved file. If a valid save is found, the game will load and display the saved state. If no save exists, the program will inform the player of the invalid choice.
- Should the player choose to start a new game, a fresh and randomized gameplay experience will be generated.


## fruitpool.cpp
(Attach direct link here)
- The file contains all the possible types of fruits based on text, each with colors represented by ANSI escape codes. 


## utils.cpp
(Attach direct link here)
- The utilities file contains all the functions involved in the game.
 ### 1. Game Board Generation
   - The function generates and displays the game board for a fruit-matching game. It first determines the maximum length of the fruit names in the fruitnames vector to set an appropriate block width for display, adding padding for centering. It then prints the column numbers, ensuring each number is centered within its block. After drawing a separator line, the function iterates through each row and column of the board, checking if each card has been revealed. If revealed, it displays the corresponding fruit with color formatting; if not revealed, it shows an asterisk. The function calculates padding dynamically based on the actual content length, excluding color codes, to ensure proper alignment. Finally, it prints a closing separator line, completing the visual representation of the game board.
  
 ### 2. Save Game Function
   - The file *‘game_saved.txt’* is where the current gameplay process will be recorded. It begins by opening the file for writing and checks for errors. The function then writes the board dimensions, time limit, number of pairs found, total pairs, and elapsed time. It iterates through the game board to record the indices of the fruits in the fruit pool, followed by the revealed status of each card (1 for revealed, 0 for hidden). It also saves the deck size and the indices of the cards in the fruit pool, along with the size and names of the fruits. Additionally, it captures the state of whether the first card has been flipped and its coordinates if applicable. Finally, the function closes the file and confirms that the game has been successfully saved.
    
 ### 3. Load Game Function
  - The function depends on the *4.Initializing Saved Game* process, which checks the required inputs by opening the file ‘game_save.txt’ If the file is empty, the function returns an invalid input message. If the file contains data, all necessary variables are initialized to match the saved game conditions. This includes generating the board, fruit pairs, and deck as per the saved state. The time limit is adjusted to reflect the saved condition, deducting the time already used. Once all these processes are complete, the file is closed.
    
 ### 4. Initializing Saved Game
  - The file ‘game_save.txt’ is opened to reveal the saved board, revealed fruits, deck, fruit pool, rows, columns, time limit, pairs found, total pairs, elapsed time, whether a card was revealed, and what the card is. All the following variables are then sent to *3.Load Game Function* for proper initializing.
    
 ### 5. Save Game or Quit Game Option
  - The function is triggered after each pair of fruits is found or not found. It prompts the user to input the desired row and column to continue gameplay, save their progress (S), or quit (Q).
  - Upon receiving a row or column input, the function checks if the values are within the board limits. It then provides feedback, either revealing a fruit or indicating an invalid choice.
  - If the user selects S, the output is directed to the 2.Save Game Function. If Q is chosen, the game will end.

 ### 6. Difficulty Level Selection
  - The function begins by presenting the available difficulty options: Easy (E), Medium (M), Hard (H), and Custom (C). The user is then prompted to input their choice. 
   - If the selection is one of E, M, or H, the function forwards the input to the 1.Game Board Generation, where predefined criteria are applied. If the user selects C for Custom, the function will request input for the desired number of rows, columns, and time limit, which will then be sent to *1.Game Board Generation* for processing.

 ### 7. Fisher-Yates Shuffle Algorithm
   - The function starts by initializing the random number generator based on the current time. It then iterates backward through the vector, which represents the board game size, starting from the last element down to the second element. For each element at index i, it generates a random index j between 0 and i. The fruits at indices i and j are then swapped. The output moves to *1.Game Board Generation.*


## record.cpp
(Attach direct link here)
*The records file contains all the functions involved in saving gameplay.*

  ### 1. Sort Gameplay Difficulty
   - Based on the user’s most recent gameplay, the difficulty level is converted into a numerical variable for processing with (1) easy, (2) medium, (3) hard, and (4) custom.
     
  ### 2. Sorting Gameplay Records
  - The function inserts a new game record into a sorted linked list, maintaining order based on difficulty and time spent. It first checks if the list is empty or if the new record should be placed at the head based on its difficulty and time spent. If so, it updates the head to point to the new record. If the new record doesn’t belong at the head, the function iterates through the list to find the correct insertion point. It compares the difficulty of the new record with the next record in the list, as well as their time spent, to maintain the sorting criteria. Once the appropriate position is found, it links the new record into the list by adjusting pointers, ensuring the list remains sorted after the insertion.

  ### 3. Print Gameplay Records
  - The function displays the game history from a linked list of gamerecord entries. It begins by printing a header for the game history. If the list is empty (i.e., no records), it outputs a message indicating that there are no past records. If records exist, the function iterates through the linked list, starting from the head. For each record, it prints the record number, difficulty level, time spent (formatted to two decimal places), and the timestamp of when the game was played. The loop continues until all records have been displayed, ensuring a clear and organized presentation of the game history.
    
  ### 4. Save New Gameplay
  - Saves the game records from a linked list to a file named *‘records.txt.’* It opens the file for writing and initializes a pointer, to traverse the linked list starting from the head. As it iterates through each gamerecord, it writes the difficulty, time spent, and timestamp to the file, separating each value with a comma and ending each record with a newline. The function continues this process until all records have been written to the file, effectively creating a persistent log of the game history that can be referenced later.

  ### 5. Load Saved Gameplay
  - It initializes by reading game records from *‘records.txt.’* and inserts them into a sorted linked list. It starts by opening the file for reading and checks if the file opened successfully. If not, the function simply returns. It then reads each line from the file in a loop. For each line, it parses the difficulty, time spent (converted from string to double), and timestamp, which are separated by commas. A new record is created with this parsed data, and the *2. Sorting Gameplay Records* is called to insert the new record into the linked list while maintaining the correct order. This process continues until all records from the file have been loaded into the list.
    
  ### 6. Gameplay Timestamp
  - Through retrieving the current time,  it is then converted into local time then used to build a timestamp string. The year is adjusted by adding 1900, and the month is incremented by 1 since it ranges from 0 to 11. The day, hour, minute, and second are formatted with leading zeros for consistency. Finally, the function returns the constructed timestamp as a string, providing a clear representation of the current date and time.
    
  ### 7. Delete All Gameplay Records
  - To remove all game records from the linked list, it starts by iterating through the list and deleting each record while advancing the head pointer. After clearing the list, it sets head to nullptr and calls *4. Save New Gameplay* to update the records file, ensuring it is empty. Finally, it prints a message confirming that all records have been deleted.


## game.cpp
(Attach link here)
*This file is involved in executing the game.*

  ### 1. Initializing Gameplay
  - The game starts with the function *runProgram* to manage the gameplay loop for a memory matching game where players flip cards to find matching fruit pairs. It starts by determining whether to load a saved game *(in record.cpp: 5. Load Saved Gameplay)* or create a new one, initializing variables such as the grid size, deck of fruits, and tracking systems for revealed cards and elapsed time. If starting fresh, the game ensures a valid grid size *(in utils.cpp: 1. Game Board generation)* and generates a shuffled deck using the Fisher Yates Shuffle *(in utils.cpp: 7. Fisher-Yates Shuffle Algorithm)*. 
  - The main loop continues until all pairs are found or the time limit expires, allowing the player to select cards and check for matches, hiding mismatches after a short delay. Time tracking is handled using chrono, and the game state can be saved if the player exits early *(in utils.cpp: 5. Save Game or Quit Game Option).* Upon completion, the game records the difficulty level, completion time, and current timestamp, updating sorted high scores and offering the option to delete records *(in record.cpp)*  Throughout the process, the game keeps updating the board, displaying feedback messages, and ensuring smooth interaction. 

### 2. Replay Game Option
  - The function prompts the player to decide whether they want to play again by entering 'y' for yes or 'n' for no. It takes the user's input, converts it to uppercase for consistency, and determines the next action based on their response. If the player enters 'Y', the function returns true signaling the game should restart. If the player enters 'N', it outputs a farewell message and returns false, ending the game. If the input is invalid, the function recursively calls itself, repeatedly prompting the user until a valid response is provided. 
