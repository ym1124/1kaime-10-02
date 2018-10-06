#include"all.h"
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
	//�w�i���C���[�p����//�̗p����Ȃ炿���Ƃ����Ƃ��ɏ���
	int cloud_gh;
	int move_x = 0;
	cloud_gh = LoadGraph("Data/Image/BG_cloud.png", true);
	//
	int color = GetColor(150, 155, 155);
	int j = 0;
	int cnt = -1;
	int reset_rng = 0;
	//**************************************
	int snowanim_x=0, snowanim_y=0, animCnt=0;
	int snow_gh = LoadGraph("Data/Image/snow.png");
	//�K�i�p******************************************
	block stairs[6];//bl_x��������bl_y	�������ύX�����C���X�^���X���ŏ��ɂł���̂ŏ����l�͑傫�����Ă���(-���ƃ��[�v���Ă���)
	block stairs1[6];
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
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				se->start_flg = true;
			}
			if (se->start_flg == true)
			{
				se->moveString();
			}
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
			reset_rng = rand() % 6;

			setStairsAll(100, cnt, BLACK_WORLD, stairs);//�I�u�W�F�N�g�Z�b�g
			setStairsAll(700, cnt, WHITE_WORLD, stairs1);

			//�ŏ��̐����ƃ��Z�b�g�����ƃ_��
			if (stairs[2].bl_x + stairs[2].set_x + 32 < 0 && reset_rng == 5)//�����_�����Z�b�g
				resetStairs(stairs);
			if (stairs1[2].bl_x + stairs1[2].set_x + 32 < 0 && reset_rng == 3)//�����_�����Z�b�g
				resetStairs(stairs1);
			//********************************************************************
			if (CheckHitKey(KEY_INPUT_0))
			{
				se->doTitleMode();
			}
			if (CheckHitKey(KEY_INPUT_5))
			{
				se->nowscene = OVER;
			}
			//�v���C���[�`��
			pl->Jump();
			pl->Draw();
		}

		//�w�i���C���[�p����
		if (cnt > 300)
		{
			/*move_x -= 5;
			if (move_x < -WINDOW_X)move_x = 0;
			DrawModiGraph(
				move_x, 0,
				WINDOW_X + move_x, 0,
				WINDOW_X + move_x, WINDOW_Y,
				move_x, WINDOW_Y,
				cloud_gh, true);
			DrawModiGraph(
				move_x + WINDOW_X, 0,
				move_x + WINDOW_X * 2, 0,
				move_x + WINDOW_X * 2, WINDOW_Y,
				move_x + WINDOW_X, WINDOW_Y,
				cloud_gh, true);*/

			DrawRectExtendGraph(0, 0, WINDOW_X, WINDOW_Y, snowanim_x * 256, snowanim_y * 256, 256, 256, snow_gh, true);
			animCnt++;
			snowanim_x = animCnt/20% 8;
			snowanim_y = animCnt/20% 3;
			/*if (snowanim_y == 3 && snowanim_x == 5) { snowanim_x = 0; snowanim_y = 0; }*/
		}

		if (se->nowscene == OVER)
		{
			se->doOverMode(&cnt,sc);
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