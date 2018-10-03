#include"all.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{

	ChangeWindowMode(true);

	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

	DxLib_Init();

	SetDrawScreen(DX_SCREEN_BACK);

	back *bk = new back();
	block *bl = new block();
	player *pl = new player();
	scene *se = new scene();
	block stairs[6];//�K�i�p
	setStairs(stairs);
	pl->setPlayerPos();

	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();

		//�^�C�g�����
		if (se->nowscene == TITLE)
		{
			bk->drawTitle();
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				se->start_flg = true;
			}
			if (se->start_flg == true)
			{
				se->doPlaymode();
			}
		}

		if (se->nowscene == PLAY)
		{
			//�w�i�`��
			bk->drawPlay();

			//�u���b�N�`��
			bl->All();
			//�K�i�`��
			stairsAll(stairs,pl);
			if (pl->worldchange == 0)setStairs(stairs);
			if (pl->worldchange==1)setStairsMirror(stairs);//set�n��������ĂԂ̂͂悭�Ȃ��̂Ō�ŕς���
			if (stairs[3].bl_x < 0)resetStairs(stairs);

			if (CheckHitKey(KEY_INPUT_0))
			{
				se->doTitlemode();
			}

			//�v���C���[�`��
			pl->setPlayerPos();
			pl->Jump();
			pl->Draw();
		}

		ScreenFlip();
	}

	delete bk;
	delete bl;

	DxLib_End();



	return 0;

}