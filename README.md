

# Vampires Survivor

# Tiên Minh Hoà-22021144

# Game description:
 * Player will become a Demon that have to struggle with many enemies in the Dark Forest. Your mission is control the Demon in order to attack and dodge the enemies as long as you can. In addition, player can collect the exp and coins which spill out after an enemy is defeated. Once you get enough exp, you can upgrade temporarily some Components  of your Demon like: HP, you Weapon,... However, the power of enemies can increase whenever you upgrade. Be careful!!!!!
  *  When your Demon die, you can come back to the Start status and go to the Store to Purchase and upgrade you components permanently.
![running](https://github.com/chienthancoder/Vampire_Game/assets/114821401/df3c9a5b-24b1-431b-a069-1d4fc0da577b)

# Tutorial:  
* Use "Right,Left,UP,Down" arrow to change your choice when game start.   
 ![Start](https://github.com/chienthancoder/Vampire_Game/assets/114821401/1c109980-e6b0-4eb6-aba8-280a954f920b)
* Press "j" in order to confirm your choice. 
* Use your mouse when choose the Component to upgrade Component temporarily
    ![upgrade](https://github.com/chienthancoder/Vampire_Game/assets/114821401/ecae5e29-cc1e-4c06-89cf-25001eac475c)
 * Use "a,d,s,w" to control your Demon.(Make sure that you turn off the Unicode)
# Game engine:
 * Use the ECS(Entities-Component System).  
 * Almost all stuffs in my Game are Entities which are in Entity Class. They have their own Components which are in Component Class.  
 * The Components of each Entity are inherited from Component Class.  
 * All of these Entities are managed by Manager Class.  
    ![ECS](https://github.com/chienthancoder/Vampire_Game/assets/114821401/7b54731c-2d59-4e86-b6f2-ae5e75451e91)
# Resource Of Games:
 * Use the resources of Vampire Survivor. You can download Game from Steam, or Cracked version through this link:
    https://daominhha.net/vampire-survivors/.
# Some classes in Game:  
* Game: this is main class that manage everything in this game like: update(), Game_Start(), Game_Lose(),store(),...  
* TextureManager: this class is used to load and Copy texture to renderer.  
* Map: Load and copy map to renderer.  
* Vector2D: this is the class that can define the direction and movement of entity in this Game.  
* Components classes: these are the classes that define the Components of entities in Game. These inherited from Class Component in ECS. This Game use some knowledge about OOP.  
  
  
  # How to run Game
 * To run Game, you can download ZIP, then click on Game.exe file.  
 * If you clone my code, you need to open cmd in the file containing Game, then type "mingw32-make".  
 * After waiting 30 seconds, you can click on file Game.exe to play.


