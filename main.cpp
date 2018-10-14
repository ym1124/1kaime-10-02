#include"DxLib.h"
#include"define.h"
#include"back.h"
#include"player.h"
#include "object.h"
#include"scene.h"
#include"effect.h"
#include"UI.h"
#include "controller.h"
#include <stdlib.h>
#include <time.h>

//TODO
//���Z�b�g���艻
//�u���b�N��������
//�w�i
//�R�C���A�Z�b�g
//���Ƃ���
//�W�����v����
//���̑��ςȋ����C��
//���y BGM/�ۂ����݂����ȉ��H

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
	spark sparks2[MAX_SPARK];
	Score *sc = new Score();
	coin *co = new coin();
	player *pl_dummy = new player();
	pl_dummy->pos_x = 0;

	pl->setPlayerPos();
	sc->getScore();
	setParticleSe(sparks);
	int color = GetColor(255, 255, 255);
	int j = 0;
	int cnt = -1, dummycnt = 500000, temp_cnt = 0;
	int reset_rng = 0;
	int pad;//�W���C�p�b�h�̓��͏�Ԋi�[�p�ϐ�
	//�K�i�p******************************************
	block stairs[6];//bl_x��������bl_y	�������ύX�����C���X�^���X���ŏ��ɂł���̂ŏ����l�͑傫�����Ă���(-���ƃ��[�v���Ă���)
	block stairs1[6];
	block stairs2[6];
	block stairs3[6];

	block walls[3];
	block walls0[3];
	block walls2[3];
	block walls3[3];
	//***********************************************
	while (ProcessMessage() != -1)
	{
		srand((unsigned int)(time(NULL)));
		ClearDrawScreen();
		//�^�C�g�����
		if (se->nowscene == TITLE)
		{
			bk->drawTitle();
			se->doTitleMode(pad);
			//�p�[�e�B�N��
			if (pl->jflg == true || pl->pos_x < -32) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32�p�̉��o�ǉ����邩��
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); } }//�Ë���
			pl->banJump(pad);
			pl->Draw();
		}

		if (se->nowscene == TUTORIAL)
		{
			se->tutorial_cnt++;
			bk->drawPlay();
			pl->Move(pl, walls);
			pl->Move(pl, walls0);
			if (pl->pos_x < -31)//�����f�B���C
			{
				if (se->tutorial_cnt_temp == 0)
				{
					se->tutorial_cnt_temp = se->tutorial_cnt;
				}
				if ((se->tutorial_cnt) - (se->tutorial_cnt_temp) > 1) //�W�����v�p�[�e�B�N���Ǝ��S�p�[�e�B�N���͕ʂɕ�����
				{
					for (j = 0; j < MAX_SPARK; j++)
					{
						sparks2[j].particle_flg = true;
						if (sparks2[5].particle_flg == true)
						{
							for (j = 0; j < MAX_SPARK; j++)
							{
								sparks2[j].sparkAll(0, WINDOW_X / 2);
								sparks2[j].drawSpark();
							}
						}
					}
				}
				if ((se->tutorial_cnt) - (se->tutorial_cnt_temp) > 100)
				{
					for (j = 0; j < MAX_SPARK; j++)sparks2[j].Valid = 0;
					pl->pos_x = POS_X_INIT;
					se->tutorial_cnt_temp = 0;
				}
			}
			if (pl->jflg == true) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32�p�̉��o�ǉ����邩��
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); } }//�Ë���
			pl->Jump(pad);
			pl->Draw();

			setWallsAll(100, se->tutorial_cnt, BLACK_WORLD, walls);
			setWallsAll(200, se->tutorial_cnt, WHITE_WORLD, walls0);
		}

		if (se->nowscene == PLAY)
		{
			cnt++;
			//�w�i�`��
			bk->drawPlay();

			//�p�[�e�B�N��
			if (pl->jflg == true) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32�p�̉��o�ǉ����邩��
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); } }//�Ë���

			if (pl->pos_x < -32)
			{
				if(pl->pos_x==-35)PlaySoundMem(sparks[0].particle_se, DX_PLAYTYPE_BACK);//-5�Â����Ă邩��-35
				if (temp_cnt == 0)temp_cnt = cnt;
				if (cnt - temp_cnt > 1)
				{
					for (j = 0; j < MAX_SPARK; j++)
					{
						sparks2[j].particle_flg = true;
						if (sparks2[5].particle_flg == true)
						{
							for (j = 0; j < MAX_SPARK; j++)
							{
								sparks2[j].sparkAll(0, WINDOW_X / 2);
								sparks2[j].drawSpark();
							}
						}
					}
				}
				//�Q�[���I�[�o�[
				if (cnt - temp_cnt > 100)
				{
					se->endGame(pl, pad);
					temp_cnt = 0;
					for (j = 0; j < MAX_SPARK; j++)sparks2[j].Valid = 0;
				}
			}
			//�K�i�ݒ�
			//********************************************************************
			reset_rng = rand() % 7;

			setStairsAll(100, cnt, BLACK_WORLD, stairs);//�I�u�W�F�N�g�Z�b�g
			setStairsAll(700, cnt, WHITE_WORLD, stairs1);
			setStairsAll(300, cnt, BLACK_WORLD, stairs2);
			setStairsAll(1300, cnt, WHITE_WORLD, stairs3);

			setWallsAll(150, cnt, BLACK_WORLD, walls2);
			setWallsAll(220, cnt, WHITE_WORLD, walls3);


			//�ŏ��̐����ƃ��Z�b�g�����ƃ_��
			if (stairs[2].bl_x + stairs[2].set_x + 32 < 0 && reset_rng == 5)//�����_�����Z�b�g
				resetStairs(stairs);
			if (stairs1[2].bl_x + stairs1[2].set_x + 32 < 0 && reset_rng == 3)//�����_�����Z�b�g
				resetStairs(stairs1);
			if (stairs2[2].bl_x + stairs2[2].set_x + 32 < 0 && reset_rng == 1)//�����_�����Z�b�g
				resetStairs(stairs2);
			if (stairs3[2].bl_x + stairs3[2].set_x + 32 < 0 && reset_rng == 6)//�����_�����Z�b�g
				resetStairs(stairs3);

			resetWalls(walls2);
			resetWalls(walls3);

			//********************************************************************
			//�R�C��
			co->coinAll(*pl, sc);
			if (reset_rng == 2)co->coinReset();
			co->Debug();

			//�v���C���[�`��
			if (pl->worldchange == BLACK_WORLD) {
				pl->Move(pl, stairs);
				pl->Move(pl, stairs2);
				pl->Move(pl, walls2);
			}
			else {
				pl->Move(pl, stairs1);
				pl->Move(pl, stairs3);
				pl->Move(pl, walls3);
			}
			pl->Jump(pad);
			pl->Draw();

			//�w�i���C���[
			bk->drawLayerAll(cnt);

			/*SetFontSize(20);
			DrawFormatString(30, 30, color, "cnt:%d,reset_rng:%d", cnt, reset_rng);*/
			sc->viewScore(cnt);
		}

		if (se->nowscene == OVER)
		{
			sc->overCnt++;
			se->doOverMode(&cnt, sc, pl, pad);
			sc->viewEndScore();
			//�w�i���C���[
			bk->drawLayerAll(dummycnt);//��~�点��J�E���g
		}
		pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		debugController(pad);
		ScreenFlip();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || (pad&(1 << 11)))
		{
			delete bk;
			delete pl;
			delete sc;
			delete se;
			delete co;
			delete pl_dummy;
			delete[] sparks;
			delete[] sparks2;

			break;
		}
	}
	DxLib_End();
	return 0;
}