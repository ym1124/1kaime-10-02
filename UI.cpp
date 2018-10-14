#pragma once
#include "DxLib.h"
#include "UI.h"

void Score::setScore(int *cnt)
{
	nowscore = *cnt;
	if (nowscore > highscore)
	{
		fp = fopen("score.dat", "wb");
		fwrite(&nowscore, sizeof(int), 1, fp);
		fclose(fp);
	/*	fp = fopen("score.dat", "wb");
		fwrite(sc, sizeof(sc), 1, fp);
		fclose(fp);*/
	}
}

void Score::getScore()
{
	fp = fopen("score.dat", "rb");
	fread(&highscore, sizeof(int), 1, fp);
	fclose(fp);
	//fp = fopen("score.dat", "rb");
	//fread(sc, sizeof(sc), 1, fp);
	//fclose(fp);
}

void Score::viewEndScore()
{
	SetFontSize(50);
	if(overCnt/60%2==1)
	DrawFormatString(50, 50, GetColor(255, 255, 255), "今回のスコア:%d 最高スコア:%d", nowscore, highscore);//名前入れたい
}

void Score::viewScore(int cnt)
{
	nowscore = cnt;
	SetFontSize(20);
	DrawFormatString(50, 50, GetColor(0, 0, 0), "スコア:%d", nowscore);
}