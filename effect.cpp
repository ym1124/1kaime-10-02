#include "all.h"

void spark::drawSpark()
{
	if (Valid == 1)
	{
		switch (anim_flg)
		{
		case 0:
			anim_x++;
			anim_x2--;
			if (anim_x >= 10)anim_flg = 1;
			break;
		case 1:
			anim_y++;
			anim_y2--;
			if (anim_y >= 10)anim_flg = 2;
			break;
		case 2:
			anim_x--;
			anim_x2++;
			if (anim_x <= 0)anim_flg = 3;
			break;
		case 3:
			anim_y--;
			anim_y2++;
			if (anim_y <= 0)anim_flg = 0;
			break;
		}
		if (Y <= WINDOW_Y / 2)DrawBox(X+anim_x, Y+anim_y, X + anim_x2, Y + anim_y2, GetColor(0, 0, 0), true);
		else if(Y > WINDOW_Y/2)DrawBox(X + anim_x, Y + anim_y, X + anim_x2, Y + anim_y2, GetColor(255, 255, 255), true);
	}
}

void spark::createSpark(int x, int y)
{
	/*int i;*///�悭�Ȃ��H

	// �g���Ă��Ȃ��Ήԃf�[�^��T��
	/*for ( i = 0; i < MAX_SPARK; i++)
	{
		if (Valid == 0) break;
	}*/

	// �����g���Ă��Ȃ��Ήԃf�[�^����������ΉԂ��o��
	/*if (i != MAX_SPARK)
	{*/
	if (Valid == 0) {
		// �ΉԂ̈ʒu��ݒ�
		X = x;
		Y = WINDOW_Y / 2;

		// �ړ��͂�ݒ�
		Sx = GetRand(7) - 3;
		Sy = -GetRand(7)+3;

		// �ΉԂ̏d�����Z�b�g
		G = GetRand(0);

		// �ΉԂ̖��邳�Z�b�g
		Bright = 255;

		// �Ήԃf�[�^���g�p���ɃZ�b�g
		Valid = 1;
	}
	//}
}

// �ΉԈړ�����
void spark::moveSpark()
{
	// �Ήԃf�[�^��������������X�L�b�v
	if (Valid == 0);

	else {
		// �ʒu���ړ��͂ɉ����Ă��炷
		Y += Sy;
		X += Sx;

		// �ړ��͂�ύX
		Sy += G;

		// �ΉԂ̖��邳��������
		Bright -= 2;

		// �ΉԂ̖��邳���O�ȉ��ɂȂ�����Ήԃf�[�^�𖳌��ɂ���
		if (Bright < 0) Valid = 0;
	}
}

void spark::sparkAll(int x,int y)
{
	createSpark(x, y);
	moveSpark();
}

void spark::jumpSpark(player *pl)
{
	if (pl->worldchange == BLACK_WORLD&&pl->jflg==true&&pl->changef==true)//���̂ւ��
	{
		if (particle_seflg == false)
		{
			PlaySoundMem(particle_se, DX_PLAYTYPE_BACK);
			particle_seflg = true;
		}
		sparkAll(pl->pos_x, pl->pos_y);
		drawSpark();
	}
	if (pl->worldchange == WHITE_WORLD&&pl->jflg == true && pl->changef == true)//���̂ւ�����₩�璼��
	{
		if (particle_seflg == false)
		{
			PlaySoundMem(particle_se, DX_PLAYTYPE_BACK);
			particle_seflg = true;
		}
		sparkAll(pl->pos_x, pl->pos_y);
		drawSpark();
	}

	if (pl->jflg == false && pl->changef == true)
	{
		particle_flg = false;
		particle_seflg = false;
		Bright = -1;
		drawSpark();
	}
}

void setParticleSe(spark *sp)
{
	sp[0].particle_se = LoadSoundMem("Data/Music/se/strange_bell.mp3");
}