// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include<Windows.h>
#include <dos.h>
#include <time.h>
#define MAXSNAKESIZE 100
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}




class Point
{
	private:
		int x;
		int y;
public:
	Point()
	{
		x = y = 10;
	}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	
	void setPoint(int x, int y)
	{
		this->x = x;
		this->y = y;

	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	void MoveUp()
	{
		y--;
	}void MoveDown()
	{
		y++;
	}void MoveLeft()
	{
		x--;
	}void MoveRight()
	{
		x++;
	}
	void Draw()
	{
		gotoxy(x, y);
		std::cout << "*";
	 
	}
	void Erase()
	{
		gotoxy(x, y);
		std::cout << " ";
	}
	void CopyPos(Point* p)
	{
		p->x = x;
		p->y = y;
	}
	void Debug()
	{
		std::cout << "(" << x << "," << y << ")";
	}
};


class Snake
{
private:
	Point * cell[MAXSNAKESIZE];//array of point to represent snake
	int size;//current size of snake
	char dir;//current dir of snake 
	Point fruit;

public:
	Snake()
	{
		size = 1;//default size
		cell[0] = new Point(20, 20);//default position
		for (int i = 1; i < MAXSNAKESIZE; i++)
		{
			cell[i] = NULL;

		}

		fruit.setPoint(rand()%50 , rand()% 25);
	}
	void AddCell(int x , int y)
	{
		cell[size++] = new Point(x, y);
		
	}
	void TurnUp()
	{
		dir = 'w';

	}
	void TurnDown()
	{
		dir = 's';

	}
	void TurnLeft()
	{
		dir = 'a';

	}
	void TurnRight()
	{
		dir = 'd';

	}
	void Move()
	{
		//clear screen
	    system("cls");
		
		//making snake body follow his head
		for (int i = size - 1; i > 0; i--)
		{
			cell[i-1]->CopyPos(cell[i]);
		}
		//turning snakes head
		switch (dir)
		{
		case 'w':
			cell[0]->MoveUp();
			break;
		case 'a':
			cell[0]->MoveLeft();
			break;
		case 's':
			cell[0]->MoveDown();
			break;
		case 'd':
			cell[0]->MoveRight();
			break;
		}
		//colliion with fruit
		if (fruit.getX() == cell[0]->getX() && fruit.getY() == cell[0]->getY())
		{
			AddCell(0,0);
			fruit.setPoint(rand() % 50, rand() % 25);
		}
		//drawing snake
		for (int i = 0; i < size; i++)
		{
			cell[i]->Draw();
			fruit.Draw();
			Debug();
			Sleep(100);
		}
		
	}
	void Debug()
	{
		for (int i = 0; i < size; i++)
		{
			cell[i]->Debug();
		}
	}
};
int main()
{//random generation of no
	srand((unsigned)time(NULL));



	//Testing Snake
	char op = 'l';
	Snake snake;
	do {
		if (_kbhit())
		{
			op = _getch();
		}
		switch (op)
		{
		case 'w':
		case'W':
			snake.TurnUp();
			break;
		case 'a':
		case'A':
			snake.TurnLeft();
			break;
		case 's':
		case'S':
			snake.TurnDown();
			break;
		case 'd':
		case'D':
			snake.TurnRight();
			break;
		}
		snake.Move();

	} while (op != 'e');


	return 0;
}

