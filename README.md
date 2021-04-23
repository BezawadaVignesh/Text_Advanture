# Text_Advanture_Game
 This is a text advanture game written in c++.
##AIM
 In this game the player need to find and kill all the enemies in the map to win the game. 
## DESCRIPTION
- Initialy player has 100 health points, when the player lost all the health points he loses the game. Player loses his health on passing through some rooms, or when he try to kill an enemy with out required equipments, or eating some uneatable things. And to gain he has to consume food or some drinks.
- __Navigation:__ Each room may have doors to some other rooms, only in the four directions: east, south, west, north. The player can move to other rooms with the command "go east" (similarly for other directions). If there is a door to that direction, the player is moved to that room. Otherwise the program prints some kind of error message (and the player stays in that room).
- __Objects:__ Various objects are populated in the rooms initially . Some of the objects are useful (needed to kill the enemies), but some may not be. "take xxx" to pick up the object xxx.The player can also issue the command "list items" to list all items picked.
- __Enemies:__ There are some enemies in the game, is in some initial room, and can be killed by some object or some combination of objects with command "kill xxx" if the program will check whether the player possesses all the objects required to kill this enemy. If so, the enemy is dead.  If the player issue the kill command but does not have the correct set of objects to kill that enemy, the enemy will attack the player and the player loses 50 health points If the player issue any other command instead (in a room with enemies), such as trying to leave the room, there is a 50% chance that the enemy will attack and so the player dies. In the other 50% chance the attack doesn't happen and the player's command is actioned.
	
  ## COMMANDS
        
	- "quit" through this command you can quit the game.
	- "help" this command gives a besic information about game.
	- "list item" this command lists all the items you picked.
	- "health" shows your health.
	- "describe" prints the room name and describes about the it. It can be also writen as "desc".
	- "about" this is used to know about a object. This is used as "about xxx".
	- "consume" this is used to consume any item they picked. This is used as "consume xxx".
	- "take" this command is used to pick items. This is used as "take xxx".
	- "look" this command is used to know objects in the room. This is used as "look xxx".
	- "go" this command is used to go from one room to other. This is used as "go xxx".
	- "kill" this command is used to kill the enemy. This is used as "kill xxx".
	- "save" this is used to save the game process.
	
  ## HOW TO RUN
  
  	- There is a main.exe file included you can run that or you can build the files by following method. 
    	- To use json files in C++ I used json.hpp header file which you can get from [github.com/nlohmann/json/tree/develop/single_include/nlohmann](https://github.com/nlohmann/json/tree/develop/single_include/nlohmann). Downlode the file and copy it in the current directory.
	- Now you can be build an executable by command "g++ -std=c++14 main.cpp -o main" in both linux and windows, or type "make" in linux.
	````g++ -std=c++14 main.cpp -o main````
	
	
