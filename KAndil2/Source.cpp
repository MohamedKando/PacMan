#include <SFML/Window.hpp>
#include<fstream>
#include<iostream>
#include<SFML/Audio.hpp>
#include <string>
#include <sstream>
#include<vector>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
void st(int);
void aboout();
void state_sol(int);
int x = 0;
string number();
//bool home();
void buttons(RenderWindow& Window);
// UNASSIGNED is used for empty cells in sudoku grid 
#define UNASSIGNED 0 

// N is used for the size of Sudoku grid. 
// Size will be NxN 
#define N 9 

bool FindUnassignedLocation(int grid[N][N],
	int& row, int& col);

bool isSafe(int grid[N][N], int row,

	int col, int num);

struct sol {
	int grid[N][N];
};

vector<sol>all_sols;

bool getDup(int gird[N][N], int sol[N][N]) {
	int k = 0;
	for (int w = 0; w < N; w++) {
		for (int i = 0; i < N; i++) {
			if (gird[w][i] == sol[w][i])k++;
		}

	}

	if (k == N * N)   return true;
	else
		return false;

}


bool SolveSudoku(int grid[N][N])
{
	int row, col;

	if (!FindUnassignedLocation(grid, row, col))
		return true;

	for (int num = 1; num <= 9; num++)
	{
		if (isSafe(grid, row, col, num))
		{
			grid[row][col] = num;

			if (SolveSudoku(grid)) {
				sol arr;
				for (int w = 0; w < N; w++) {
					for (int i = 0; i < N; i++) {
						arr.grid[w][i] = grid[w][i];
					}
				}
				bool ok = false;

				for (int w = 0; w < all_sols.size(); w++) {
					if (getDup(grid, all_sols[w].grid))ok = true;
				}

				if (!ok)
					all_sols.push_back(arr);

			}


			grid[row][col] = UNASSIGNED;
		}
	}
	return false;
}

bool FindUnassignedLocation(int grid[N][N],
	int& row, int& col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (grid[row][col] == UNASSIGNED)
				return true;
	return false;
}

bool UsedInRow(int grid[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
		if (grid[row][col] == num)
			return true;
	return false;
}

bool UsedInCol(int grid[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
		if (grid[row][col] == num)
			return true;
	return false;
}

bool UsedInBox(int grid[N][N], int boxStartRow,
	int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + boxStartRow]
				[col + boxStartCol] == num)
				return true;
	return false;
}

bool isSafe(int grid[N][N], int row,
	int col, int num)
{
	return !UsedInRow(grid, row, num) &&
		!UsedInCol(grid, col, num) &&
		!UsedInBox(grid, row - row % 3,
			col - col % 3, num) &&
		grid[row][col] == UNASSIGNED;
}


void printGrid(int grid[N][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
			cout << grid[row][col] << " ";
		cout << endl;
	}
}
Music music;
Music music2;
int main()
{
	int pressCounter = 0;

	RenderWindow window(VideoMode(1366, 768), "sudoku");
	Font fo;
	Texture background;
	background.loadFromFile("graphics/3.jpg");
	fo.loadFromFile("font/font.ttf");
	Sprite backg(background);

	Text play, setting, about, checkedplay, checkedsettings, checkedabout, exit, checkedexit;

	Texture texture2, texture3;
	RectangleShape rectangle2, rectangle3;



	if (!music.openFromFile("music/Music2.wav"))
	{
		cout << "could open the song" << std::endl;
	}



	play.setFont(fo);
	play.setString("play");
	play.setCharacterSize(75);
	play.setFillColor(Color::Black);
	play.setPosition(550, 350);

	checkedplay.setFont(fo);
	checkedplay.setString("play");
	checkedplay.setCharacterSize(75);
	checkedplay.setFillColor(Color::Red);
	checkedplay.setPosition(550, 350);

	setting.setFont(fo);
	setting.setString("import sudoku");
	setting.setCharacterSize(75);
	setting.setFillColor(Color::Black);
	setting.setPosition(550, 450);

	checkedsettings.setFont(fo);
	checkedsettings.setString("import sudoku");
	checkedsettings.setCharacterSize(75);
	checkedsettings.setFillColor(Color::Red);
	checkedsettings.setPosition(550, 450);

	about.setFont(fo);
	about.setString("about");
	about.setCharacterSize(75);
	about.setFillColor(Color::Black);
	about.setPosition(550, 550);

	checkedabout.setFont(fo);
	checkedabout.setString("about");
	checkedabout.setCharacterSize(75);
	checkedabout.setFillColor(Color::Red);
	checkedabout.setPosition(550, 550);

	exit.setFont(fo);
	exit.setString("exit");
	exit.setCharacterSize(75);
	exit.setFillColor(Color::Black);
	exit.setPosition(550, 650);

	checkedexit.setFont(fo);
	checkedexit.setString("exit");
	checkedexit.setCharacterSize(75);
	checkedexit.setFillColor(Color::Red);
	checkedexit.setPosition(550, 650);


	while (window.isOpen())
	{

		if (pressCounter > 3 || pressCounter < 0)
			pressCounter = 0;

		Event chose;
		while (window.pollEvent(chose))
		{

			switch (chose.type) {
			case Event::KeyPressed:
				switch (chose.key.code)
				{
				case Keyboard::Down:
					pressCounter++; break;
				case Keyboard::Up:
					pressCounter--; break;


				default:
					break;
				}
			}
			if (chose.type == sf::Event::Closed)
				window.close();
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i mousepos = sf::Mouse::getPosition(window);
				if ((mousepos.x >= 50 && mousepos.x <= 90) && (mousepos.y >= 50 && mousepos.y <= 90))
				{
					music.play();
				}
				if ((mousepos.x >= 50 && mousepos.x <= 90) && (mousepos.y >= 100 && mousepos.y <= 140))
				{
					music.stop();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::M))
			{
				music.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				music.stop();
			}

		}
		//window.clear();

		switch (pressCounter)
		{
		case 0:
			window.draw(backg);
			window.draw(checkedplay);
			window.draw(setting);
			window.draw(about);
			window.draw(exit);
			buttons(window);
			break;
		case 1:
			window.draw(backg);
			window.draw(play);
			window.draw(checkedsettings);
			window.draw(about);
			window.draw(exit);
			buttons(window);
			break;
		case 2:
			window.draw(backg);
			window.draw(play);
			window.draw(setting);
			window.draw(checkedabout);
			window.draw(exit);
			buttons(window);
			break;
		case 3:
			window.draw(backg);
			window.draw(play);
			window.draw(setting);
			window.draw(about);
			window.draw(checkedexit);
			buttons(window);
			break;
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			switch (pressCounter)
			{
			case 0:
				window.close();
				st(0);
				break;
			case 1:   window.close();
				st(1);
				break;
			case 2:
				window.close();

				aboout();

				break;
			case 3:
				window.close();
			}
		}
		buttons(window);
		window.display();

	}

}

void st(int n)
{

	string** gridd = new string *[N];
	for (int i = 0; i < N; i++)
	{
		gridd[i] = new string[N];
	}
	string** arr = new string *[N];
	for (int i = 0; i < N; i++)
	{
		arr[i] = new string[N];
	}

	int grid[N][N];
	string content;
	ifstream in("c.txt");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			in >> grid[i][j];

		}
	}
	in.close();

	ifstream inn("c.txt");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			inn >> gridd[i][j];

		}
	}
	inn.close();


	SolveSudoku(grid);

	if (all_sols.size() != 0) {
		cout << "Num of Sols:" << all_sols.size() << endl;

	}
	else
		cout << "No solution exists";

	for (int w = 0; w < all_sols.size(); w++) {
		cout << "Solution " << w + 1 << endl << endl << endl;

		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				cout << all_sols[w].grid[i][k] << " ";
			}
			cout << endl;
		}

	}

	string p;
	stringstream*** ptr3D = NULL;
	ptr3D = new stringstream * *[all_sols.size() + 1];

	for (int i = 0; i < N; i++)
	{
		ptr3D[i] = new stringstream *[N];

		for (int j = 0; j < N; j++)
		{
			ptr3D[i][j] = new stringstream[N];


		}
	}
	RenderWindow window(VideoMode(1366, 768), "sudoku");

	Sprite slogo, sgame, sbackground;
	Texture  logo, game, background;
	logo.loadFromFile("graphics/7.png");
	game.loadFromFile("graphics/9x9.jpg");
	if (n == 0)
		background.loadFromFile("graphics/back0.jpg");
	else
		background.loadFromFile("graphics/back1.jpg");
	slogo.setTexture(logo);
	sgame.setTexture(game);
	sbackground.setTexture(background);

	slogo.setPosition(750, 30);

	Text solve, checkedsolve, exit, checkedexit, numsol;

	Font fo;
	fo.loadFromFile("font/font.ttf");
	Text choose;

	choose.setFont(fo);
	//score.setString(content);
	choose.setCharacterSize(30);
	choose.setFillColor(Color::Green);
	//score.setPosition(630, 120);

	numsol.setFont(fo);
	numsol.setCharacterSize(50);
	numsol.setFillColor(Color::Blue);
	numsol.setPosition(600, 250);
	if (n == 1) {
		stringstream pp;
		pp << "Number of solutions = " << all_sols.size();
		numsol.setString(pp.str());
	}

	solve.setFont(fo);
	solve.setString("solve");
	solve.setCharacterSize(75);
	solve.setFillColor(Color::Blue);
	solve.setPosition(750, 350);

	checkedsolve.setFont(fo);
	if (n == 0) {
		checkedsolve.setString("Check the solution");
		checkedsolve.setCharacterSize(50);
	}
	else {
		checkedsolve.setString("solve");
		checkedsolve.setCharacterSize(75);
	}
	checkedsolve.setFillColor(Color::Red);
	checkedsolve.setPosition(650, 350);

	exit.setFont(fo);
	exit.setString("exit");
	exit.setCharacterSize(75);
	exit.setFillColor(Color::Blue);
	exit.setPosition(750, 550);

	checkedexit.setFont(fo);
	checkedexit.setString("exit");
	checkedexit.setCharacterSize(75);
	checkedexit.setFillColor(Color::Red);
	checkedexit.setPosition(750, 550);
	int intarr[N][N];
	int w = 0;
	int count = 0;
	int counter = 0;
	string exportt;
	stringstream ss[N][N];
	int pressCounter = 0;
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{

				
				main();
			}


			if (n == 0)
			{
				for (int i = 0; i < N; i++)
				{
					for (int g = 0; g < N; g++)
					{
						if (Mouse::isButtonPressed(Mouse::Left))
							if (Mouse::getPosition(window).x >= (g * 62) && Mouse::getPosition(window).x <= ((g + 1) * 62) &&
								Mouse::getPosition(window).y >= (i * 59) && Mouse::getPosition(window).y <= ((i + 1) * 59) && gridd[i][g] == '0')
							{
								exportt = number();

								//cout << gridd[i][g] << i << "  " << g << "  " << exportt << endl;
								gridd[i][g] = exportt;

							}

					}

				}


				if (Keyboard::isKeyPressed(Keyboard::M))
				{
					music.play();
				}
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					music.stop();
				}

				if (event.type == Event::KeyPressed) {

					if (Keyboard::isKeyPressed(Keyboard::Key::Space))
					{
						for (int i = 0; i < N; i++)
						{
							for (int g = 0; g < N; g++)
							{
								ss[i][g] << gridd[i][g];
								ss[i][g] >> intarr[i][g];

							}

						}
						for (int w = 0; w < all_sols.size(); w++) {
							if (counter == N * N)
								break;
							counter = 0;
							for (int i = 0; i < N; i++) {
								for (int k = 0; k < N; k++) {
									if (intarr[i][k] == all_sols[w].grid[i][k])
										counter++;

								}

							}

						}
						if (counter == N * N) {
							state_sol(1);
							window.close();
						}
						else {

							state_sol(0);
							x = 1;
							window.close();
						}

					}

				}
			}

			

			if (n == 1)
			{


				if (event.type == Event::KeyPressed) {

					if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
					{




						for (int i = 0; i < N; i++) {
							for (int k = 0; k < N; k++) {
								ptr3D[w][i][k] << all_sols[w].grid[i][k];

								ptr3D[w][i][k] >> arr[i][k];
								//cout << all_sols[w].grid[i][k] << " ";
							}
							//	cout << endl;
						}
						//cout << all_sols.size() << " " << w << endl;

						gridd = arr;


						if (n == 1)
						{
							stringstream pp;
							pp << "Number of solutions = " << count + 1;
							numsol.setString(pp.str());
						}


						if (w < all_sols.size())
						{
							w++; //count++;
							if (w == 5)
							{

								w = 0;

							}
							if (count < all_sols.size() - 1)
							{
								count++;
							}
						}


					}
				}

			}



		}

		window.clear();
		window.draw(sbackground);
		window.draw(slogo);
		window.draw(sgame);

		for (int i = 0; i < N; i++)
		{
			for (int g = 0; g < N; g++)
			{
				content = gridd[i][g];
				if (content == '0')
					content = "";
				choose.setPosition((g + 0.35) * 62, (i + 0.33) * 59);
				choose.setString(content);
				window.draw(choose);
				window.draw(numsol);
				window.draw(checkedsolve);


			}
		}

		window.display();

	}

	cout << endl << counter;

	for (int i = 0; i < N; i++)
	{
		delete gridd[N];

	}
	delete[] gridd;

	for (int i = 0; i < N; i++)
	{
		delete arr[N];

	}
	delete[] arr;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			delete[] ptr3D[i][j];
		}
		delete[] ptr3D[i];
	}
	delete ptr3D;

	//window.close();
}

string number()
{
	RenderWindow window(VideoMode(500, 400), "sudoku", Style::None);
	Font fo;
	fo.loadFromFile("font/font.ttf");
	Text text;
	string display;
	text.setFont(fo);
	text.setCharacterSize(20);
	text.setStyle(Text::Bold);
	text.setFillColor(Color::White);
	text.setPosition(100, 200);
	text.setStyle(Text::Bold);
	stringstream s;
	s << "ENTER THE NUMBER :  ";
	text.setString(s.str());

	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::TextEntered)
			{

				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					if (display.size() > 0)
						window.close();
				}

				if (event.text.unicode >= 48 && event.text.unicode <= 57)
					display = (char)event.text.unicode;

				else if (event.text.unicode == 8 && display.size() > 0)
					display.erase(display.size() - 1);
				stringstream s;
				s << "ENTER THE NUMBER :  " << display;
				text.setString(s.str());

			}
		}

		window.clear();
		window.draw(text);
		window.display();
	}
	return display;
}


void state_sol(int x)
{
	Music music2;

	if (!music2.openFromFile("music/Music3.wav"))
	{
		cout << "could open the song" << std::endl;
	}
	Music music3;

	if (!music3.openFromFile("music/Music4.wav"))
	{
		cout << "could open the song" << std::endl;
	}

	RenderWindow window(VideoMode(500, 400), "sudoku", Style::None);
	Font fo;
	fo.loadFromFile("font/font.ttf");
	Texture gi;
	if (x == 1)
	{
		gi.loadFromFile("graphics/winer1.jpg");

		music2.play();
		music.stop();
	}

	else
	{

		gi.loadFromFile("graphics/loser.jpg");
		music3.play();
		music.stop();
	}
	Sprite sgif;
	sgif.setTexture(gi);
	while (window.isOpen())
	{


		window.clear();
		window.draw(sgif);

		window.display();
	}
	//main();
}


void buttons(RenderWindow& Window)
{

	Texture texture2;
	Texture texture3;

	RectangleShape rectangle2;
	RectangleShape rectangle3;

	texture2.loadFromFile("graphics/white_musicOn.jpeg");
	rectangle2.setTexture(&texture2);
	rectangle2.setPosition(sf::Vector2f(50, 50));
	rectangle2.setSize(sf::Vector2f(40, 40));

	texture3.loadFromFile("graphics/white_musicOff.jpeg");
	rectangle3.setTexture(&texture3);
	rectangle3.setPosition(sf::Vector2f(50, 100));
	rectangle3.setSize(sf::Vector2f(40, 40));


	Window.draw(rectangle2);
	Window.draw(rectangle3);

}

void aboout()
{
	RenderWindow window(VideoMode(1366, 750), "sudoku");
	Font fo;
	fo.loadFromFile("font/font.ttf");
	Texture gi;

	gi.loadFromFile("graphics/about.jpg");

	Sprite sgif;
	sgif.setTexture(gi);
	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{

				window.close();
				main();
			}


		}
		window.clear();
		window.draw(sgif);

		window.display();
	}

}