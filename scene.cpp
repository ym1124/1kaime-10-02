#pragma once
#include "scene.h"
#include "UI.h"

void scene::doTitleMode(int pad)
{
	drawTitleMenu(pad);
	drawString();
	DrawFormatString(300, 300, GetColor(255,255,255), "START�������ŃQ�[���J�n�I");
}

void scene::drawTitleMenu(int pad)
{
	if (CheckHitKey(KEY_INPUT_RIGHT) || pad&(KEY_INPUT_RIGHT))t_select = 2;//
	if (CheckHitKey(KEY_INPUT_LEFT)||pad&(KEY_INPUT_LEFT))t_select = 1;//�L�[���͂��ĂȂ��Ă����̂���������
	if (longpress_cnt <= 20)
	{
		switch (t_select)
		{
		case 1:
			DrawExtendGraph(70, WINDOW_Y - 180, 340, WINDOW_Y - 50, start_gh, true);
			DrawGraph(WINDOW_X - 440, WINDOW_Y - 150, tutorial_gh, true);
			break;
		case 2:
			DrawGraph(100, WINDOW_Y - 150, start_gh, true);
			DrawExtendGraph(WINDOW_X -550, WINDOW_Y - 180, WINDOW_X - 20, WINDOW_Y - 50, tutorial_gh, true);
			break;
		}
	}
	if (t_select == 1 && CheckHitKey(KEY_INPUT_SPACE)|| pad&PAD_INPUT_A)
	{
		longpress_cnt++;
		start_flg = true;
	}
	if (t_select == 2 && (CheckHitKey(KEY_INPUT_SPACE)|| pad&PAD_INPUT_A))nowscene = TUTORIAL;
	if (start_flg == true && longpress_cnt>40)
	{
		DrawExtendGraph(70, WINDOW_Y - 180, 340, WINDOW_Y - 50, start_gh, true);
		DrawGraph(WINDOW_X - 440, WINDOW_Y - 150, tutorial_gh, true);
		moveString();
	}
}

void scene::doPlayMode()
{
	/*start_timer += 1;
	if (start_timer >= 120)
	{*/
		nowscene = PLAY;
		start_flg = false;
		/*
		start_timer = 0;
	}*/
}

void scene::doOverMode(int *cnt,Score *sc,player *pl,int pad)
{
	DrawGraph((WINDOW_X - 700) / 2, WINDOW_Y / 2 - 150, gameover_gh, true);
	switch (o_select)
	{
	case 0:
		DrawGraph(100, WINDOW_Y - 150, retry_gh, true);
		DrawGraph(WINDOW_X - 340, WINDOW_Y - 150, totitle_gh, true);
		break;
	case 1:
		DrawExtendGraph(70, WINDOW_Y-180, 340, WINDOW_Y-50,retry_gh, true);
		DrawGraph(WINDOW_X - 340, WINDOW_Y - 150, totitle_gh, true);
		break;
	case 2:
		DrawGraph(100, WINDOW_Y - 150, retry_gh, true);
		DrawExtendGraph(WINDOW_X-370, WINDOW_Y-180, WINDOW_X-100, WINDOW_Y-50, totitle_gh, true);
		break;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) || pad&(PAD_INPUT_LEFT))
	{
		o_select = 1;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) || pad&(PAD_INPUT_RIGHT))
	{
		o_select = 2;
	}
	if ((CheckHitKey(KEY_INPUT_SPACE)||pad&PAD_INPUT_A) && o_select==1)//���g���C
	{
		nowscene = PLAY;
		o_select = 0;
		pl->worldchange = WHITE_WORLD;
		pl->setPlayerPos();
		*cnt = 0;
	}
	if ((CheckHitKey(KEY_INPUT_SPACE) || pad&PAD_INPUT_A) && o_select == 2)//�^�C�g��
	{
		nowscene = TITLE;
		o_select=0;
		pl->worldchange = WHITE_WORLD;
		pl->setPlayerPos();
		*cnt = 0;
	}
	sc->setScore(cnt);
	sc->getScore();
	pl->jumpstartflg = true;
}

void scene::moveString()
{
	upperside += 4;
	downside -= 4;
	if (upperside >= WINDOW_Y&&downside <= 0)
	{
		upperside = 0;
		downside = WINDOW_Y;
		longpress_cnt = 0;
		doPlayMode();
	}
}

void scene::drawString()
{//����E��E������
	DrawModiGraph(
		0, upperside,
		WINDOW_X, upperside,
		WINDOW_X, downside,
		0,downside,
		title_string, true);
}

void scene::endGame(player *pl,int pad)
{
	if (CheckHitKey(KEY_INPUT_0)||(pad&(1<<11)))//�V�t�g���Z�Ŗ������X�^�[�g�ݒ�
	{
		nowscene = TITLE;
	}
	if (pl->pos_x<-32)//�v���C���[����ʊO�ɏo����I��
	{
		StartJoypadVibration(DX_INPUT_PAD1, 500, 1000);
		nowscene = OVER;
	}
}