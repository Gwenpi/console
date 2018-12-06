#pragma once
#pragma warning(disable:4996)
#include"ball.h"
#include"barrier.h"

#include<vector>
#include<iostream>
#include<conio.h>
#include<memory>

class Game
{
private:
	Ball *player;
	std::vector<std::unique_ptr<Barrier>>barrier;
	double m_Time;
public:
	Game();
	void update();
	void draw();
	void produceBarrier();
	bool isFailure()const;
	~Game();
private:
	void init();
	void input();
	void barrierChange();
	void hintInterface()const;
	void clearBarrier();
	void collisionCheck();
};

