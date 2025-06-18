//============================================================================
// Name        : Hamas Naveed
// Copyright   : (c) Reserved
// Description : Basic 2D game of Risk...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
//#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath>// for basic math functions such as cos, sin, sqrt
#include "game.h"
#include<fstream>
#include<conio.h>
#include<cstdlib>
#include<time.h>
using namespace std;
void territories(); // this will make the territories and it will also show player turn in the right corner 

void territory_assign(int nplayers, int xposition, int yposition); // in this one each player will select their territory in clockwise direction

bool territory_check(); // this will check if territory is owned by that person or not

void clrconvert(int clr[]); // this convert the number to the clr repected code 

bool clrcheck(int i);// this will check if the clr is already occupied or not 

void MenuDisplay(); // this will display the menu before start

void KeyboardFunc(unsigned char key, int x, int y); // this will check the buttons pressed while on menu

void MenuMousePressed(int button, int state, int x, int y); // this is check for mouse clicks

void UpdateHighScore(int playerTerritories[6]); // this will update the score 

void DisplayHighScore();// this will display the highscore from file

int  checkhighest(int nplayers);// this will check who has highest territory 

void troop_assign(int nplayers); // player will select their troops

bool player_territorycheck(int mX, int mY, int currentplayer);// this will check if territory is by whom

void position_assign(int x, int y, int nplayers); // this will assign the initial position of each player 

void before_attack(int& currentplayer, int nplayers); // this will ask the user what they want to do

void attack(int mX, int mY, int nplayers, int& currentplayer);// this is the attack will occur

void playerpostion_occupied(int tnumber, int oldplayer); //this will check if the player position is occupied or not 

void troop_place(int currentplayer, int x, int y); //this will used to place troops on the territories

int initializeCurrentPlayer(); // this will return the player with most territories and he will go first

void position_change(int& currentplayer, int nplayers, int x, int y); // this is for changing the postion of the troops and the player

void game_check();// this will check if the game has ended or not and game will end when any of the player has occupied 132 territories or more





//these are some global variables
int territory_troops[6][133] = { 0 };//this willl store the troops on each territory 
int countries[133] = { 0 }; //this will store which country belongs to which player
int p_position[6] = { 0 }; //this will store the player position
int t_troops[6][3]; // all troop information is stored in this
int nplayers = 2; //default number of players
int menuWindow; // this store the menu
string playerNames[6]; // names of the players from menu will be stored in this 
int at = 1, mov = 0, fight = 0; // these are some check varibles
int cp;// this will store whose playing and display on window 
int clr[6] = { 0 }; // this will store the colour that players will choose
bool territory_troopcheck = 0;
int placement_check = 1;
int m_troop;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
 //Board *b;
void GameDisplay()/**/ {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors


	DrawString(50, 800, "Risk Game ", colors[MISTY_ROSE]);
	DrawString(900, 800, "Players", colors[MISTY_ROSE]);

	territories();



	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key == 'a' || key == 'A')
	{

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
	{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
int position_check;
void MousePressedAndMoved(int x, int y) {

	if (x < 830 && y < 830) {
		bool isTerritoryAvailable = territory_check();

		if (isTerritoryAvailable == 1) {
			territory_assign(nplayers, x, y);
		}
		else if (territory_troopcheck == 0) {
			troop_assign(nplayers);
		}
		else if (position_check < nplayers) {
			position_assign(x, y, nplayers);
		}
		else if (placement_check <= nplayers)
		{

			static int currentplayer = initializeCurrentPlayer();
			//cout << endl << currentplayer << endl;
			cp = currentplayer;
			if (currentplayer == 0)
			{

				if (t_troops[currentplayer][0] > 0)

				{
					troop_place(currentplayer + 1, x, y);
					if (t_troops[0][0] < 1)
					{
						currentplayer++;
						placement_check++;
						if (currentplayer >= nplayers)
							currentplayer = 0;
					}

				}

			}
			else if (currentplayer == 1)
			{


				if (t_troops[currentplayer][0] > 0)
				{
					troop_place(currentplayer + 1, x, y);
					if (t_troops[1][0] < 1)
					{
						currentplayer++;
						placement_check++;
						if (currentplayer >= nplayers)
							currentplayer = 0;
					}
				}

			}
			else if (currentplayer == 2)
			{
				cout << currentplayer << endl;


				if (t_troops[currentplayer][0] > 0)
				{
					troop_place(currentplayer + 1, x, y);
					if (t_troops[2][0] < 1)
					{
						currentplayer++;
						placement_check++;
						if (currentplayer >= nplayers)
							currentplayer = 0;
					}
				}
			}
			else if (currentplayer == 3)
			{
				//cout <<endl<< currentplayer << endl;


				if (t_troops[currentplayer][0] > 0)
				{
					troop_place(currentplayer + 1, x, y);
					if (t_troops[3][0] < 1)
					{
						currentplayer++;
						placement_check++;
						if (currentplayer >= nplayers)
							currentplayer = 0;
					}
				}
			}
			else if (currentplayer == 4)
			{
				//cout << currentplayer << endl;


				if (t_troops[currentplayer][0] > 0)
				{
					troop_place(currentplayer + 1, x, y);
					if (t_troops[4][0] < 1)
					{
						currentplayer++;
						placement_check++;
						if (currentplayer >= nplayers)
							currentplayer = 0;
					}
				}
			}
			else if (currentplayer == 5)
			{
				//cout << currentplayer << endl;

				if (t_troops[currentplayer][0] > 0)
				{
					troop_place(currentplayer + 1, x, y);
					if (t_troops[5][0] < 1)
					{
						currentplayer++;
						placement_check++;
						if (currentplayer >= nplayers)
							currentplayer = 0;
					}
				}
			}


		}
		else {

			game_check();
			int num = 0;
			static int currentplayer = checkhighest(nplayers);
			cp = currentplayer;
			if (fight == 0 && mov == 0)
				before_attack(currentplayer, nplayers);

			if (fight == 1)
			{

				if (at == 0) {

					attack(x, y, nplayers, currentplayer);
					cp = currentplayer;
				}
			}
			if (mov == 1)
			{
				position_change(currentplayer, nplayers, x, y);
				cp = currentplayer;


			}


		}
	}
	else {
		cout << "Not in range" << endl;
	}

	glutPostRedisplay();
}







void MouseMoved(int x, int y) {


	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{



	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char* argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	int menuWidth = 800, menuHeight = 800;
	glutInitWindowPosition(1000, 100);
	glutInitWindowSize(menuWidth, menuHeight);
	menuWindow = glutCreateWindow("Menu");
	SetCanvasSize(menuWidth, menuHeight);

	glutDisplayFunc(MenuDisplay);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MenuMousePressed);



	srand(time(0));








	/*glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("PF Project"); // set the title of our game window
	SetCanvasSize(width, height); */// set the number of pixels.*/





	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	//glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	//glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	//glutTimerFunc(1000.0, Timer, 0);

	//glutMouseFunc(MouseClicked);
	  //glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();

	return 1;
}
#endif /* AsteroidS_CPP_ */
//const string highscoreFileName = "highscores.txt";

// Function to display high score from file
//this will read the score from the highscore and display it whenever user press !
void DisplayHighScore() {
	fstream highscoreFile;
	highscoreFile.open("highscores.txt");

	if (!highscoreFile.is_open()) {
		cout << "Highscore file not found." << endl;
		return;
	}

	cout << "High Scores:" << endl;
	string line;
	while (getline(highscoreFile, line)) {
		cout << line << endl;
	}

	highscoreFile.close();
}



void UpdateHighScore(int playerTerritories[6]) {
	string line;
	string contents[10];

	int i = 0;
	fstream highscoreFile("highscores.txt", ios::app);
	if (!highscoreFile.is_open()) {
		cout << "Error opening highscore file." << endl;
		return;
	}
	string name = playerNames[0];
	int score = playerTerritories[0];
	//highscoreFile << playerName << " - Score: " << score << endl;

	for (int i = 1; i < 6; ++i) {
		if (playerTerritories[i] > score)
		{
			score = playerTerritories[i];
			name = playerNames[i];
		}
	}
	while (getline(highscoreFile, line))
	{
		contents[i] += line;
		i++;
	}

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (playerTerritories[j] < playerTerritories[j + 1]) {
				// Swap player names
				name = playerNames[j];
				playerNames[j] = playerNames[j + 1];
				playerNames[j + 1] = name;

				// Swap territories
				score = playerTerritories[j];
				playerTerritories[j] = playerTerritories[j + 1];
				playerTerritories[j] = score;
			}
		}
	}

	for (int i = 0;i < 6;i++)
	{
		highscoreFile << playerNames[i] << " " << playerTerritories[i] << endl;
	}


	highscoreFile.close();
}
//this wiill be used to display the menu on the screens and its contents
void MenuDisplay() {
	glClearColor(0, 0, 0.6, 0.1);
	glClear(GL_COLOR_BUFFER_BIT);

	DrawString(200, 900, "Risk Game", colors[RED]);
	DrawString(200, 700, "Enter the number of players (2-6): " + to_string(nplayers), colors[RED]);
	DrawString(200, 650, "Press '+' to increase, '-' to decrease  ", colors[RED]);
	DrawString(200, 600, "Press ! to view HIGHSCORES ", colors[RED]);
	DrawString(200, 550, "Press Any UPPER-Case letter to input name ", colors[RED]);
	//DrawString(200, 500, "Press Press / to select clr of each player  ", colors[RED]);



	DrawString(200, 450, "Press 'Enter' to start the game", colors[MISTY_ROSE]);
	int yPos = 400;
	for (int i = 0; i < nplayers; ++i) {
		DrawString(200, yPos, " Player " + to_string(i + 1) + ": " + playerNames[i], colors[MISTY_ROSE]);
		yPos -= 50;
	}



	glutSwapBuffers();
}

bool namesEntered = false;
// THIS IS FOR THE MENU
//when all players have entered their names it will move to the game window
void KeyboardFunc(unsigned char key, int x, int y) {
	if (key == 13) { // 'Enter' key
		if (namesEntered) {
			// Check if the player names have been entered for all players

			glutDestroyWindow(menuWindow); // Close the menu window

			// Proceed to the main game window setup
			int width = 1020, height = 840;
			glutInitWindowSize(width, height);
			glutCreateWindow("Risk Game");
			SetCanvasSize(width, height);
			glutDisplayFunc(GameDisplay);
			glutSpecialFunc(NonPrintableKeys);
			glutKeyboardFunc(PrintableKeys);
			glutTimerFunc(1000.0, Timer, 0);
			glutMotionFunc(MousePressedAndMoved);
			glutMainLoop();
		}
	}
	else if (key == '+') {
		nplayers = (((nplayers + 1) < (6)) ? (nplayers + 1) : (6));

		cout << "Number of players: " << nplayers << endl;
	}
	else if (key == '-' && nplayers > 2) {
		nplayers--;
		cout << "Number of players: " << nplayers << endl;
	}
	else if (key == '!')
	{
		DisplayHighScore();
	}

	else {
		// Capture player names

		if (key >= 'A' && key <= 'Z') {
			for (int i = 0; i < nplayers; i++)
			{
				cout << "Enter the name of player " << i + 1 << " ";
				getline(cin, playerNames[i]);
				namesEntered = true;

			}
			for (int i = 0; i < nplayers; i++)
			{
				do
				{
					cout << "\nEnter Colour of the player " << i + 1 << endl;
					cout << "1)Red " << endl;
					cout << "2)White " << endl;
					cout << "3)Purple " << endl;
					cout << "4)Orange " << endl;
					cout << "5)Blue " << endl;
					cout << "6)Yellow " << endl;
					cin >> clr[i];
				} while (clr[i] < 1 || clr[i]>6 || clrcheck(i));
			}
			clrconvert(clr);



		}
		else {
			cout << "Invalid input. Please enter a valid name." << endl;
		}
	}
}

void MenuMousePressed(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}
}




//this function will be called everytime when display function is called 
// its to make territories on the screen 
void territories() {

	int m = 0, you = 710;

	int number = 0;


	for (int i = 0;i < 11;i++)
	{
		for (int j = 0;j < 12;j++)
		{
			number++;
			if (countries[number] == 1)
				DrawSquare(m, you, 60, colors[clr[0]]);
			else if (countries[number] == 2)
				DrawSquare(m, you, 60, colors[clr[1]]);
			else if (countries[number] == 3)
				DrawSquare(m, you, 60, colors[clr[2]]);
			else if (countries[number] == 4)
				DrawSquare(m, you, 60, colors[clr[3]]);
			else if (countries[number] == 5)
				DrawSquare(m, you, 60, colors[clr[4]]);
			else if (countries[number] == 6)
				DrawSquare(m, you, 60, colors[clr[5]]);
			else
				DrawSquare(m, you, 60, colors[2]);// 2 for brown 

			int smallx = 10, smally = 30, nums = 0;
			if (countries[number] != 0)
			{
				nums = territory_troops[countries[number] - 1][number];
				for (int tro = 0;tro < nums;tro++)
				{
					DrawSquare(m + smallx, you + smally, 5, colors[BLACK]);
					smallx += 5;
					if (tro % 5 == 0)
					{
						smally += 5;
						smallx = 10;
					}
				}
			}

			DrawString(m, you, to_string(number), colors[BLACK]);
			//DrawCircle(m + 30, you + 50, 3, colors[BLACK]);
			//DrawRectangle(m + 25, you + 30, 10, 10, colors[BLACK]);

			int yt = 750;
			int mt = 1000;
			for (int i = 0;i < nplayers;i++)
			{
				DrawString(900, yt, playerNames[i], colors[GREEN]);


				DrawSquare(mt, yt, 20, colors[clr[i]]);


				if (cp == i)
				{
					DrawCircle(870, yt, 4, colors[WHITE]);
				}
				yt -= 20;
				DrawString(900, yt, "Troop = " + to_string(t_troops[i][0]), colors[GREEN]);
				yt -= 50;
				DrawString(900, yt, "Pos = " + to_string(p_position[i]), colors[GREEN]);
				yt -= 50;


			}


			//DrawString(900, , "Troop" + to_string(m), colors[GREEN]);







			m += 70;

		}
		you -= 70;
		m = 0;
	}
}


// each player will not select their territory and this will check if the coordinate
//send from mouse moved and pressed are on the territory 
//it they are on territory they will be given to the that player 
//this it will make sure that territory is not occupied by anyone 
void territory_assign(int nplayers, int xposition, int yposition)
{
	static int currentplayer = 1;
	int tnumber = 0;
	int check = 0;

	cp = currentplayer - 1;

	for (int i = 70;i < 840;i += 70)
	{

		for (int j = 0;j < 840;j += 70)
		{
			tnumber++;

			if ((xposition<j + 60 && xposition>j) && (yposition < i + 70) && (yposition > i) && countries[tnumber] == 0)
			{
				countries[tnumber] = currentplayer;
				//cout << countries[tnumber] << tnumber << endl;
				currentplayer++;
				if (currentplayer > nplayers)
					currentplayer = 1;
				check = 1;
				if (check == 1)
					break;


			}

		}
		if (check == 1)
			break;
	}




}
// this is for moving to next portion of selection troop 
// if there is any coutry which is un occupied it will it return true 
bool territory_check()
{
	for (int k = 1;k < 133;k++)
	{
		if (countries[k] == 0)
			return 1;
	}
	return 0;
}
// this will count the territories owned by each player 
// and return the player number which has the maximum number of territories
int checkhighest(int nplayers)
{



	int playerTerritories[6] = { 0 };

	// Count the territories occupied by each player
	for (int i = 1; i < 133; i++) {
		int currentPlayer = countries[i];
		if (currentPlayer >= 1 && currentPlayer <= 6) {
			playerTerritories[currentPlayer - 1]++;
		}
	}

	int maxTerritories = playerTerritories[0];
	int maxPlayer = 0;

	for (int i = 1; i < nplayers; i++) {
		if (playerTerritories[i] > maxTerritories) {
			maxTerritories = playerTerritories[i];
			maxPlayer = i;
		}
	}
	cout << "\nPlayer " << maxPlayer + 1 << "  has the highest number of territories " << endl;

	return maxPlayer + 1;
}
// in this function every player will select their troops 
// this will be after they have selected their territories 
//everyplayer will be given 80 troop but that will reduce after adding of each player 
void troop_assign(const int  nplayers)
{
	int* t_count = new int[nplayers];
	int choice = 0, choice2 = 0, check = 0;

	// Calculate the total territories owned by each player
	for (int i = 1; i <= 132; i++)
	{
		for (int j = 0; j < nplayers; j++)
		{
			if (countries[i] == j + 1)
				t_count[j]++;
		}
	}

	// Initialize troops and infantry for each player

	for (int i = 0;i < nplayers;i++)
	{
		t_troops[i][0] = 80 - nplayers * 5; // total troops
		t_troops[i][1] = 0;                  // infantry
		t_troops[i][2] = 0;                  // cannon
	}

	for (int i = 0; i < nplayers; i++)
	{
		do
		{
			do
			{

				territories();
				cout << "\nPlayer " << i + 1 << " has " << t_troops[i][0] << " troops\n Please select your troops" << endl;
				cout << "1) Infantry" << endl;
				cout << "2) Cannon" << endl;
				cout << "3)None" << endl;
				cout << "Which type of troop do you want: ";

				cin >> choice;
			} while (choice < 1 || choice > 3);

			switch (choice)
			{
			case 1:
				do
				{
					cout << "How many Infantry do you want (Infantry = 3 troops): ";
					cin >> choice2;
				} while (choice2 < 0 || (t_troops[i][1] * 3 + 3 * choice2) > t_troops[i][0]);

				t_troops[i][1]++;
				t_troops[i][0] -= 3 * choice2;
				break;

			case 2:
				do
				{
					cout << "How many Cannon do you want (Cannon = 5 troops): ";
					cin >> choice2;
				} while (choice2 < 0 || (t_troops[i][2] * 5 + 5 * choice2) > t_troops[i][0]);

				t_troops[i][2]++;
				t_troops[i][0] -= 5 * choice2;
				break;

			case 3:
				choice = 3;
				continue;
			default:
				cout << "An error has occurred." << endl;
				break;
			}
		} while (choice != 3);

	}

	territory_troopcheck = 1;





	cout << "\nEvery player has now received their troops." << endl;

	territory_troopcheck = 1;
}
// this is for placing the troops on thier territory 
// troop will only be placed if the player own that territory
void troop_place(int currentplayer, int mX, int mY)
{
	{
		int tnumber = 0;
		//cout << endl<<currentplayer << endl;
		if (mX < 840 && mY < 840 && mX > 0 && mY > 70)
		{
			for (int i = 70; i < 840; i += 70)
			{
				for (int j = 0; j < 840; j += 70)
				{
					tnumber++;

					if ((mX < j + 60 && mX > j) && (mY < i + 70) && (mY > i))
					{
						if (countries[tnumber] == currentplayer)
						{
							cout << "\n Troop added on territory " << tnumber;
							t_troops[currentplayer - 1][0]--;
							territory_troops[currentplayer - 1][tnumber]++;
							return;


						}
						else
							return;
					}
				}
			}
		}

	}
}
//this will convert the clr to the code of the clr player had choosen 
void clrconvert(int clr[])
{
	for (int i = 0;i < nplayers;i++)
	{
		if (clr[i] == 1)
		{
			clr[i] = 5;
		}
		else if (clr[i] == 2)
		{
			clr[i] = 137;

		}
		else if (clr[i] == 3)
		{
			clr[i] = 80;

		}
		else if (clr[i] == 4)
		{
			clr[i] = 15;

		}
		else if (clr[i] == 5)
		{
			clr[i] = 68;

		}
		else if (clr[i] == 6)
		{
			clr[i] = 23;

		}

	}
}
//this will check wheather the clr is already occupied or not 
bool clrcheck(int i)
{
	for (int k = 0;k < i;k++) {
		if (clr[i] == clr[k])
			return 1;
	}

	return 0;

}
// this will for selecting the initial position of each player from where they will start 
void position_assign(int x, int y, int nplayers)
{
	static int currentplayer = 1;
	cout << "Enter your position Player " << currentplayer << " \n";

	if (player_territorycheck(x, y, currentplayer))
	{

		currentplayer++;
		position_check++;

	}


}
//yeh p_position mien har player ki position assign kr dein ga 
//agr auski wo territory houii
bool player_territorycheck(int mX, int mY, int currentplayer)
{
	int tnumber = 0;
	if (mX < 840 && mY < 840 && mX > 0 && mY > 70)
	{
		for (int i = 70; i < 840; i += 70)
		{
			for (int j = 0; j < 840; j += 70)
			{
				tnumber++;

				if ((mX < j + 60 && mX > j) && (mY < i + 70) && (mY > i))
				{
					if (countries[tnumber] == currentplayer)
					{
						p_position[currentplayer - 1] = tnumber;
						cout << "Player " << currentplayer << " selected territory: " << tnumber << endl;  //output
						territory_troops[currentplayer - 1][p_position[currentplayer - 1]] += m_troop;
						return true;
					}
				}
			}
		}
	}
	return false;
}
//this will give choose to the user what they wan to do 
//after selection this the choice function be called

//in mv function user will select how many troop they want to move and where 
//after telling the number of troops they will move to select their postion 
void before_attack(int& currentplayer, int nplayers)
{
	cp = currentplayer;

	int choice = 0;
	do {
		cout << "Current position of Player " << currentplayer + 1 << " is " << p_position[currentplayer];
		cout << "\n Do you want to " << endl;
		cout << "1)Attack " << endl;
		cout << "2)Move" << endl;
		cout << "3)Pass" << endl;
		cin >> choice;
	} while (choice < 1 || choice > 3);

	switch (choice) {
	case 1:
		cout << "Select your territory on the map to attack ";
		fight = 1;
		at = 0;


		break;
	case 2:

		do
		{

			cout << "How many troop do you want to move " << endl;
			cin >> m_troop;

		} while (m_troop > territory_troops[currentplayer][p_position[currentplayer]] && m_troop > t_troops[currentplayer][0]);
		if (m_troop < territory_troops[currentplayer][p_position[currentplayer]])
			territory_troops[currentplayer][p_position[currentplayer]] -= m_troop;
		else
			t_troops[currentplayer][0] -= m_troop;
		cout << "Where do you want to move ";

		mov = 1;
		break;
	case 3:
		cout << "You turn is passed " << endl;
		currentplayer++;
		if (currentplayer + 1 > nplayers)
			currentplayer = 0;
		break;
	}

}
// this will be called when player choose move fucntion 
// this will move the player to the next positon 
//this will also check if the player own that territory which they are moving to 
void position_change(int& currentplayer, int nplayers, int x, int y)
{
	if (player_territorycheck(x, y, currentplayer + 1))
	{

		currentplayer++;
		if (currentplayer >= nplayers)
			currentplayer = 0;

		mov = 0;
		cp = currentplayer;



	}
}
// this will be called when user chooses attack 
// it will make sure they are attacking to the adjacent territory 
//and if that is owned buy that same person 
// if they even they get an card which will be contain additional territories
void attack(int mX, int mY, int nplayers, int& currentplayer)
{
	int tnumber = 0, dice1, dice2, tp;
	cp = currentplayer;
	for (int i = 70; i < 840; i += 70)
	{
		for (int j = 0; j < 840; j += 70)
		{
			tnumber++;

			if ((mX < j + 60 && mX > j) && (mY < i + 70) && (mY > i))
			{
				if (countries[tnumber] != currentplayer + 1)
				{
					if ((tnumber - p_position[currentplayer] == 1) || (tnumber - p_position[currentplayer] == 12) ||
						(tnumber - p_position[currentplayer] == -1) || (tnumber - p_position[currentplayer] == -12))
					{

						dice1 = rand() % 6;
						dice2 = rand() % 6;
						if (dice1 >= dice2)
						{
							cout << "\nAttack successful " << endl;
							int oldplayer = countries[tnumber];
							countries[tnumber] = currentplayer + 1;
							playerpostion_occupied(tnumber, oldplayer);

							tp = rand() % 10;
							cout << "You got a card " << endl;
							cout << "You got " << tp << " troops ";
							t_troops[currentplayer][0] += tp;


							at = 1;
							fight = 0;

							// Increment currentplayer when the player wins
							currentplayer++;
							if (currentplayer >= nplayers)
								currentplayer = 0;
							cp = currentplayer;
							return;
						}
						else
						{
							cout << "\nYou have lost  " << endl;
							fight = 0;
							at = 1;

							// Increment currentplayer when the player loses
							currentplayer++;
							if (currentplayer >= nplayers)
								currentplayer = 0;
							cp = currentplayer;
							return;
						}
					}
				}
				else
				{

					at = 0;
					return;
				}
			}
		}
	}


}

void playerpostion_occupied(int tnumber, int oldplayer)
{


	for (int k = 0;k < nplayers;k++)
	{
		if (tnumber == p_position[k])
		{
			for (int i = 0; i < 133; i++) {
				if (countries[i] == oldplayer)
				{
					p_position[oldplayer - 1] = i;
					if (i != tnumber)
					{
						cout << "\nPlayer " << oldplayer << " new position is " << p_position[oldplayer - 1] << endl;
						return;
					}

				}

			}
		}
	}
}

//this will roll 6 dice and whoever got the largest dice will start first
//int will return the player number who got the largest dice
// it will also check if new dice is not matched to the previous dice
// if it matches it will again roll a dice 
int initializeCurrentPlayer() {
	static int check = 0;
	static int num = 0;
	int dice[6] = { 0 };

	srand(time(0));

	for (int i = 0; i < nplayers; i++) {
		do {
			dice[i] = rand() % 6 + 1;

			// Check if the generated value is equal to any previous value
			for (int j = 0; j < i; j++) {
				if (dice[j] == dice[i]) {
					// If equal, generate a new value
					dice[i] = rand() % 6 + 1;
					j = -1; // j will be incremented to 0 in the next iteration
				}
			}

			// If no match is found, break out of the loop
		} while (false);

		cout << "Player " << i + 1 << " got " << dice[i] << endl;
	}

	int max = dice[0];
	num = 0;

	for (int i = 0; i < nplayers; i++) {
		if (max < dice[i]) {
			max = dice[i];
			num = i;
		}
	}
	cout << "Starting player is " << num + 1;
	check = 1;
	return num;
}
// this will check if any player has occupied all the territories 
// there score and name will moved to update the file highscore data
void game_check() {
	int playerTerritories[6] = { 0 };

	// Count the territories occupied by each player

	for (int i = 0; i < 133; i++) {
		int currentPlayer = countries[i];
		if (currentPlayer >= 1 && currentPlayer <= 6) {
			playerTerritories[currentPlayer - 1]++;
		}
	}



	for (int i = 0; i < 6; i++) {
		if (playerTerritories[i] > 132) {
			cout << "Player " << i + 1 << " has occupied more than 132 territories!" << endl;
			UpdateHighScore(playerTerritories);
			exit(1);
		}
	}
}






