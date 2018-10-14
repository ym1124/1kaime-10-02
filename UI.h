#pragma once
#include <string>
using namespace std;
class Score
{
public:
	int nowscore=0,highscore=0;
	int overCnt = 0;
	FILE *fp;
	string playername="tako";
	void setScore(int *cnt);
	void getScore();
	void viewScore(int cnt);
	void viewEndScore();
	Score(){}
};

