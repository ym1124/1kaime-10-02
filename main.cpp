#include"DxLib.h"
#include"define.h"
#include"back.h"
#include"player.h"
#include"scene.h"
#include"effect.h"
#include"UI.h"
#include <stdlib.h>
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{

	ChangeWindowMode(true);

	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

	DxLib_Init();

	SetDrawScreen(DX_SCREEN_BACK);

	back *bk = new back();
	player *pl = new player();
	scene *se = new scene();
	spark sparks[MAX_SPARK];
	Score *sc = new Score();

	pl->setPlayerPos();
	sc->getScore();
	setParticleSe(sparks);
	int color = GetColor(150, 155, 155);
	int j = 0;
	int cnt = -1;
	int reset_rng = 0;
	//�K�i�p******************************************
	block stairs[6];//bl_x��������bl_y	�������ύX�����C���X�^���X���ŏ��ɂł���̂ŏ����l�͑傫�����Ă���(-���ƃ��[�v���Ă���)
	block stairs1[6];
	block stairs2[6];
	block stairs3[6];
	//***********************************************
	while (ProcessMessage() != -1)
	{
		srand((unsigned int)(time(NULL)));

		ClearDrawScreen();
		//�^�C�g�����
		if (se->nowscene == TITLE)
		{
			bk->drawTitle();
			se->drawString(); 
			//�p�[�e�B�N��
			if (pl->jflg == true || pl->pos_x < -32) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32�p�̉��o�ǉ����邩��
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); } }//�Ë���

			if (pl->worldchange == BLACK_WORLD) {
				pl->Move(pl, stairs);
			}
			else {
				pl->Move(pl, stairs1);
			}
			if (pl->jumpstartflg == true)//�^�C�g����ʂŘA���W�����v�����Ȃ�����
			{
				pl->Jump();
				if(pl->worldchange==BLACK_WORLD&&pl->pos_y==POS_Y_INIT)
					pl->jumpstartflg = false;
			}
			pl->Draw();
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				se->longpress_cnt++;
				se->start_flg = true;
			}
			if (se->start_flg == true&&se->longpress_cnt>60)
			{
				se->moveString();
			}
			DrawFormatString(300, 300, color, "�X�y�[�X�������ŃX�^�[�g");
		}

		if (se->nowscene == PLAY)
		{
			cnt++;
			//�w�i�`��
			bk->drawPlay();

			//�p�[�e�B�N��
			if (pl->jflg == true || pl->pos_x < -32) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32�p�̉��o�ǉ����邩��
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); }}//�Ë���

			//�K�i�ݒ�
			//********************************************************************
			reset_rng = rand() % 7;

			setStairsAll(100, cnt, BLACK_WORLD, stairs);//�I�u�W�F�N�g�Z�b�g
			setStairsAll(700, cnt, WHITE_WORLD, stairs1);
			setStairsAll(300, cnt, BLACK_WORLD, stairs2);
			setStairsAll(1300, cnt, WHITE_WORLD, stairs3);

			//�ŏ��̐����ƃ��Z�b�g�����ƃ_��
			if (stairs[2].bl_x + stairs[2].set_x + 32 < 0 && reset_rng == 5)//�����_�����Z�b�g
				resetStairs(stairs);
			if (stairs1[2].bl_x + stairs1[2].set_x + 32 < 0 && reset_rng == 3)//�����_�����Z�b�g
				resetStairs(stairs1);
			if (stairs2[2].bl_x + stairs2[2].set_x + 32 < 0 && reset_rng == 1)//�����_�����Z�b�g
				resetStairs(stairs2);
			if (stairs3[2].bl_x + stairs3[2].set_x + 32 < 0 && reset_rng == 6)//�����_�����Z�b�g
				resetStairs(stairs3);
			//********************************************************************
			if (CheckHitKey(KEY_INPUT_0))
			{
				se->doTitleMode();
			}
			if (pl->pos_x<-32)//�v���C���[����ʊO�ɏo����I��
			{
				se->nowscene = OVER;
			}
			//�v���C���[�`��
			if (pl->worldchange == BLACK_WORLD) {
				pl->Move(pl, stairs);
				pl->Move(pl, stairs2);
			}
			else {
				pl->Move(pl, stairs1);
				pl->Move(pl, stairs3);
			}
			pl->Jump();
			pl->Draw();
		}

		//�w�i���C���[
		bk->drawLayerAll(cnt);

		if (se->nowscene == OVER)
		{
			se->doOverMode(&cnt,sc,pl);
			sc->viewScore();
		}

		DrawFormatString(30, 30, color, "cnt:%d,reset_rng:%d", cnt, reset_rng);

		ScreenFlip();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			delete bk;

			break;
		}
	}

	DxLib_End();
	return 0;
}