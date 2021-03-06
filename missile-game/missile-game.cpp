// Gameplay Programming
// Practical
// Text Based Missile Game
// Name: Alan Bolger
// Student No: C00232036

#include <iostream>
#include <time.h>
#include <string>

const short nuclearRange = 75;
const short nuclearTurns = 5;
const short explosiveRange = 50;
const short explosiveTurns = 8;

int setLaunchCode(); // Forward declaration

// Calculate distance between target and player's missile
int calculateDistance(int coordinatesX, int coordinatesY, int targetX, int targetY)
{
	return static_cast<int>(std::sqrt(((targetX - coordinatesX) * (targetX - coordinatesX)) + 
		((targetY - coordinatesY) * (targetY - coordinatesY))));
}

// Display text
void printText(std::string t_string)
{
	std::cout << t_string << std::endl;
}

// Print line
void printLine()
{
	printText("-----------------------------------------------------------------------");
}

// Print space
void printSpace()
{
	printText("");
}

// Get number with validation
int numberInput(std::string t_text)
{
	int n;
	printText(t_text);
	std::cin >> n;

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		printLine();
		printText(t_text);
		std::cin >> n;
	}

	return n;
}

// Position
typedef struct Position
{
	int x;
	int y;

	void print()
	{
		std::cout << x << y << std::endl;
	}

}Coordinates;

// Warhead type
enum WarHead
{
	EXPLOSIVE,
	NUCLEAR
};

// Enemy position
typedef struct Enemy
{
	Coordinates coordinates;
}Target;

// Missile struct, holds gameplay
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
		short range; // Blast radius of warhead
		int availableTurns;
		int distance; // Enemy's distance form impact
		int enemyHealth = 100;
		int damage; // Enemy damage
		char warheadInput;
		WarHead warheadChoice;
		int launchCode; // Random launch code
		int codeEntry;
		int breakLoop = false; // Used for breaking out of while loops

		// Intro text
		printText("TEXT BASED MISSILE GAME");
		printLine();
		printText("You are the commander of an army. The enemy is located somewhere");
		printText("on an island that measures 300km x 300km. It is your job to work");
		printText("out where the enemy is located, and to destroy them!");
		printSpace();
		printText("Every time a warhead explodes, the enemy's distance from the");
		printText("warhead's impact will be displayed. By observing the distance, you");
		printText("can then make suitable adjustments to your warhead's target");
		printText("coordinates on your next turn.");
		printSpace();
		printText("Choosing to go nuclear will allow you to fire 5 nuclear warheads.");
		printText("Nuclear warheads have a blast radius of 75km.");
		printSpace();
		printText("Choosing to use explosives will allow you to fire 8 explosive");
		printText("warheads. Explosive warheads have a blast radius of 50km.");
		printLine();

		// Choose warhead type
		while (!breakLoop)
		{
			printText("Select warhead (N = Nuclear x 5 / E = Explosive x 10): ");
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
				printText("Enter a valid value!");
				printLine();
				break;
			}
		}

		// Set warhead range and player's turn amount
		switch (warheadChoice)
		{
		case NUCLEAR:
			range = nuclearRange;
			availableTurns = nuclearTurns;
			break;

		case EXPLOSIVE:
			range = explosiveRange;
			availableTurns = explosiveTurns;
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
				codeEntry = numberInput("Enter the launch code:");

				if (codeEntry == launchCode)
				{
					arm();
					printLine();
					printText("Warhead armed!");
					breakLoop = true;
				}
				else
				{
					printLine();
					printText("The launch code doesn't match - Try again!");
				}
			}

			printLine();
			printText("Enter coordinates of where you wish to fire your warhead:");
			coordinates.x = numberInput("X coordinate should be between 0 and 300km (or you'll miss the island!)");
			coordinates.y = numberInput("Y coordinate should be between 0 and 300km (or you'll miss the island!)");

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
				std::cout << "Target missed by " << (distance - range) << "km" << std::endl;
			}

			availableTurns--;
			printLine();
			std::cout << "Warheads left: " << availableTurns << std::endl;
			std::cout << "Enemy health is " << enemyHealth << "%" << std::endl;

			breakLoop = false;

			if (enemyHealth <= 0)
			{
				printLine();
				printText("You have destroyed the enemy!");
				availableTurns = 0;
			}
		}

		printLine();
		printText("Game over!");
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

// Everybody needs a main
int main()
{
	game.gamePlay();
	return 0;
}