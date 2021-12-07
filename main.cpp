using namespace std;
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>


void gameLoop();
void initializeRandomSeed();
void initializeRandomEnemy();
void fight();
void home();

//home
bool hasVistedHome = false;
bool pixieCoreAssembled = false;
int pixieCoreFragments = 0;
int pixieCoreFragmentTotal = 100;
//	crafting
bool hasOpenedCrafting = false;


//player
/*
enemyState
	0 defending
	1 attacking
*/
string playerName = "Drittz";
int playerState = 0;
int playerHpMax = 13;
int playerHp = playerHpMax;
int playerAtk = 11;
int playerDef = 12;

//enemy
/*
enemyState
	0 defending
	1 attacking
*/
string enemyName = "Foul Animal";
int enemyState = 0;
int enemyHp = 3;
int enemyAtk = 1;
int enemyDef = 4;
int enemyDefOriginal = enemyDef;


int main() {
	initializeRandomSeed();
	gameLoop();
	return 1;
}
void gameLoop() {
	if (playerHp <= 0)
	{
		cout << "You feel your soul try to ascend, yet something\n holds you down.\n You hear a "
			<< "faint whisper, 'Not yet.'.\n";
	}
	int choice = -1;
	int randomWalkFight = -1;
	cout << "You're in the woods.\n" << "1:Walk." << endl << "2:Meditate."
		<< endl << "3:Go Home." << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		//random 50 50 chance attack or pleasant walk


		 /* generate number between 1 and 10: */
		randomWalkFight = rand() % 10 + 1;
		switch (randomWalkFight) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			cout << "You walked and nothing bad happened."
				<< endl << "How pleasant!!!" << endl;
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			fight();
			break;
		}
		break;
	case 2:
		if (playerHp < playerHpMax) {
			playerHp++;
			cout << "You gained a tiny bit of health and you consider some of the\nrealities of existing.\n";
		}
		else cout << "You are already well, but you still wonder about the coming eschaton.\n";
			break;
	case 3:
		cout << "You went Home." << endl;
		home();
			break;
	}
	gameLoop();
}

void initializeRandomSeed() {
	/* initialize random seed: */
	srand(time(NULL));
}

void fight() {
	int choice;
	initializeRandomEnemy();
	cout << "How unfortunate." << endl << "A foul animal approaches." << endl
		<< "1:Attack" << endl << "2:Defend" << endl;
	cin >> choice;
	switch (choice) {
	case 1:
		playerState = 1;
		//decide if enemy is defending or attacking
		enemyState = rand() % 2;
		//if defending subtract playerAtk from enemyDef then enemyHp if there is any left over.
		if (enemyState == 0) {
			enemyDef -= playerAtk;
			if (enemyDef > 0)
			{
				if (enemyDefOriginal - playerAtk < 0)
				{
					enemyHp += enemyDefOriginal - playerAtk;
				}
			}
			cout << "You attacked the " << enemyName;
		}

		break;
	case 2:
		playerState = 0;
		break;
	}
	if (enemyHp < 0)cout << "The " << enemyName << "died" << endl;
	else {
		if (enemyState == 1) {
			cout << "The enemy is attacking" << endl;
			if (playerState == 0)playerHp -= playerDef - enemyAtk;
			else if (playerState == 1)playerHp -= enemyAtk;
			if (playerHp > 0)cout << "You survived and " << enemyName << " ran away." << endl;
			else if (playerHp < 0)cout << "You died and " << enemyName << " is looting your corpse." << endl;
		}
	}
	return;
}
void initializeRandomEnemy() {

	enemyName = "Foul Animal";

	//needless here
	enemyState = rand() % 2;
	/*
	enemyState
	   0 defending
	   1 attacking
	*/

	/* generate number between 1 and 10: */
	enemyHp = rand() % 10 + 1;
	enemyAtk = rand() % 10 + 1;
	enemyDef = rand() % 10 + 1;
	enemyDefOriginal = enemyDef;
}
void home() {
	int choice = -1;
	if (!hasVistedHome) {
		cout << "In your home you notice tiny glowing fragments\n"
			<< "of the Pixie Core.  It must have exploded again.\n"
			<< "How unfortunate, you will have to collect all of \nthem before the house has power again.\n";
		hasVistedHome = true;
	}
	if (!pixieCoreAssembled)
	{
		cout << "1.Sleep.\n2.Collect Pixie Core fragments.\n3.Leave\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "You lay in your bed, alone.  You start to feel drowsy, \nbut you feel alone.  "
				<< "You wake alone too, dreams of familiar faces\n haunt you now.  "
				<< "You are ready to face the day.  \n";
			//add in sleep bonuses maybe random quality influence atk and def bonus
			break;
		case 2:
			cout << "Reaching for the glowing fragments as they wiz by tires you.\n";
			int tempPCFragmentsCollected = rand() % 10 + 1;
			pixieCoreFragments += tempPCFragmentsCollected;
			if (tempPCFragmentsCollected < 5)cout << "You collected so little, but atleast you tried.\n";
			if (tempPCFragmentsCollected > 5)cout << "You collected so many, be thankful you tried!\n";

			if (pixieCoreFragments >= pixieCoreFragmentTotal)
			{
				pixieCoreAssembled = true;
				cout << "Your Pixie Core is now assembling itself.\n"
					<< "Your house begins humming back to life.\n"
					<< "Your CRAFTING STATION is now OPERABLE.\n";
			}
			break;
		case 3:
			cout << "You left the house, now you are in the wild.\n";
			return;
			break;
		}
	}
	else {
		cout << "1.Sleep.\n2.Craft.\n3.Leave\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "You lay in your bed, alone.  You start to feel drowsy, \nbut you feel alone.  "
				<< "You wake alone too, dreams of familiar faces\n haunt you now.  "
				<< "You are ready to face the day.  \n";
			//add in sleep bonuses maybe random quality influence atk and def bonus
			break;
		case 2:
			if (!hasOpenedCrafting)
			{
				cout << "With an active CRAFTING STATION you are once again\n"
					<< "tempted to use the power of the PIXIE CORE to\n"
					<< "boost your stats.\n";
			}
			int tempCraftingChoice = -1;
			cout << "1.Craft a better WEAPON\n2.CRAFT better ARMOR\n3.LEAVE the CRAFTING STATION";
			//add switch
			break;
		case 3:
			cout << "You left the house, now you are in the wild.\n";
			return;
			break;
		}
	}
	home();
	return;
}



