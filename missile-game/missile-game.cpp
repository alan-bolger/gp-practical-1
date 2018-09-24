// Gameplay Programming
// Practical
// Text Based Missile Game
// Name: Alan Bolger
// Student No: C00232036

#include <iostream>
#include <time.h>

int setLaunchCode(); // Forward declaration

// Calculate distance between target and player's missile
int calculateDistance(int coordinatesX, int coordinatesY, int targetX, int targetY)
{
	return static_cast<int>(std::sqrt(((targetX - coordinatesX) * (targetX - coordinatesX)) + 
		((targetY - coordinatesY) * (targetY - coordinatesY))));
}

// Print line
void printLine()
{
	std::cout << "--------------------------------------------------------------" << std::endl;
}

typedef struct Position
{
	int x;
	int y;

	void print()
	{
		std::cout << x << y << std::endl;
	}

}Coordinates;

enum WarHead
{
	EXPLOSIVE,
	NUCLEAR
};

typedef struct Enemy
{
	Coordinates coordinates;
}Target;

struct Missile
{
	WarHead payload;

	Coordinates coordinates;

	Target target;

	bool armed;

	void arm()
	{
		if (armed)
		{
			armed = false;
		}
			
		else
		{
			armed = true;
		}			
	}

	void update()
	{
		coordinates.x += 1;
		coordinates.y += 2;
	}

	void gamePlay()
	{
		std::srand(static_cast<unsigned>(time(NULL)));
		int range;
		int availableTurns;
		int distance;
		int enemyHealth = 200;
		int damage;
		char warheadInput;
		WarHead warheadChoice;
		int launchCode;
		int codeEntry;
		int breakLoop = false;

		std::cout << "TEXT BASED MISSILE GAME" << std::endl;
		printLine();
		std::cout << "In this game, the enemy target will be located at a random" << std::endl;
		std::cout << "position on an island 300km x 300km. The player must work" << std::endl;
		std::cout << "out the enemy's location by launching warheads. When a" << std::endl;
		std::cout << "warhead misses or hits the target, the enemy's distance" << std::endl;
		std::cout << "from the impact will be revealed. The player can use this " << std::endl;
		std::cout << "information to try and get their warhead closer to the target" << std::endl;
		std::cout << "on their next turn. Nuclear warheads have a damage radius of" << std::endl;
		std::cout << "120km, and explosive warheads have a damage radius of 80km." << std::endl;
		printLine();

		// Choose warhead type
		while (!breakLoop)
		{
			std::cout << "Select warhead (N = Nuclear x 5 / E = Explosive x 10): ";
			std::cin >> warheadInput;

			switch (warheadInput)
			{
			case 'N':
			case 'n':
				warheadChoice = WarHead::NUCLEAR;
				breakLoop = true;
				break;

			case 'E':
			case 'e':
				warheadChoice = WarHead::EXPLOSIVE;
				breakLoop = true;
				break;

			default:
				printLine();
				std::cout << "Enter a valid value!" << std::endl;
				printLine();
				break;
			}
		}		
		
		// Set warhead range and player's turn amount
		switch (warheadChoice)
		{
		case NUCLEAR:
			range = 120;
			availableTurns = 5;
			break;

		case EXPLOSIVE:
			range = 80;
			availableTurns = 10;
			break;
		}

		breakLoop = false;

		// Set random target coordinates
		target.coordinates.x = std::rand() % 300;
		target.coordinates.y = std::rand() % 300;

		// Game runs as long as there are more than 0 turns left
		// If the enemy dies then the amount of turns is set to 0 to break out of loop
		while (availableTurns > 0 && enemyHealth > 0)
		{
			while (!breakLoop)
			{
				printLine();
				launchCode = setLaunchCode();
				std::cout << "Enter the launch code: ";
				std::cin >> codeEntry;

				if (codeEntry == launchCode)
				{
					arm();
					printLine();
					std::cout << "Warhead armed!" << std::endl;
					breakLoop = true;
				}
				else
				{
					printLine();
					std::cout << "The launch code doesn't match - Please try again!" << std::endl;
				}
			}

			printLine();
			std::cout << "Enter coordinates of where you wish to fire!" << std::endl;
			std::cout << "X coordinate (between 0 and 300km): ";
			std::cin >> coordinates.x;
			std::cout << "Y coordinate (between 0 and 300km): ";
			std::cin >> coordinates.y;

			// Get distance between enemy target and player's missile
			distance = calculateDistance(coordinates.x, coordinates.y, target.coordinates.x, target.coordinates.y);

			printLine();

			if (distance < range)
			{
				damage = range - distance;
				enemyHealth = enemyHealth - damage;
				std::cout << "Target hit! " << damage << " damage inflicted!" << std::endl;
				std::cout << "Target is " << distance << "km away from impact zone." << std::endl;
			}
			else
			{
				std::cout << "Target missed by " << distance - range << "km" << std::endl;
			}

			availableTurns--;
			printLine();
			std::cout << "Warheads left: " << availableTurns << std::endl;
			std::cout << "Enemy health is " << enemyHealth << std::endl;

			breakLoop = false;

			if (enemyHealth <= 0)
			{
				printLine();
				std::cout << "You have destroyed the enemy!" << std::endl;
				availableTurns = 0;
			}
		}		

		printLine();
		std::cout << "Game over!" << std::endl;
		std::cout << "The enemy was positioned at " << "[" << target.coordinates.x << ", " << target.coordinates.y << "]" << std::endl;
		printLine();
		system("Pause");
		system("Exit");
	}
}game;

// Set random launch code, display and return
int setLaunchCode()
{
	int launchCode = static_cast<int>(std::rand() % 50000 + 10000);
	std::cout << "The launch code is " << launchCode << std::endl;
	return launchCode;
}

int main()
{
	game.gamePlay();
	return 0;
}