#pragma once
#include "player.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>


class spark
{
public:
	int Valid;	// ���̃f�[�^���g�p�����A�t���O
	int X, Y;	// �ΉԂ̈ʒu
	int anim_x, anim_y;
	int anim_x2, anim_y2;
	int anim_flg;
	int Sx, Sy;	// �ΉԂ̈ړ���
	int G;		// �ΉԂ̏d��
	int Bright;	// �ΉԂ̖��邳
	int particle_se;
	bool particle_flg;
	bool particle_seflg;
	spark()
	{
		particle_flg = false;
		particle_seflg = false;
		particle_se=0;
		anim_flg=0;
		anim_x = 0;
		anim_y = 0;
		anim_x2 = 10;
		anim_y2 = 10;
		Valid = 0;
	}
	void createSpark(int x, int y);	// �ΉԂ��o������
	void moveSpark();	// �ΉԈړ�����
	void drawSpark();
	void sparkAll(int x, int y);
	void jumpSpark(player *pl);
} ;

void setParticleSe(spark *sp);