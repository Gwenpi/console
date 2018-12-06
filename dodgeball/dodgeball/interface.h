#pragma once

#include"color.h"


void setWindow(int width, int height)
{
	COORD coord;
	coord.X = width;
	coord.Y = height;
	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = height - 1;
	rect.Right = width - 1;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(handle, coord);
	SetConsoleWindowInfo(handle, FALSE, &rect);
}

void hideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(handle, &cci);
	cci.bVisible = false;
	SetConsoleCursorInfo(handle, &cci);
}

COORD getxy()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	COORD coord;
	coord.X = csbi.dwCursorPosition.X;
	coord.Y = csbi.dwCursorPosition.Y;
	return coord;
}

void gotoxy(const COORD& coord)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, coord);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, coord);
}

void moveUP()
{
	COORD coord;
	coord = getxy();
	coord.Y--;
	gotoxy(coord);
}

void moveDown()
{
	COORD coord;
	coord = getxy();
	coord.Y++;
	gotoxy(coord);
}

void moveRight()
{
	COORD coord;
	coord = getxy();
	coord.X++;
	gotoxy(coord);
}

void moveLeft()
{
	COORD coord;
	coord = getxy();
	coord.X--;
	gotoxy(coord);
}


void setConsoleColor(Color foreColor= WHITE)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, foreColor | 0);
}

