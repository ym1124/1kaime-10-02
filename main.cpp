#include"all.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{

	ChangeWindowMode(true);

	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

	DxLib_Init();

	SetDrawScreen(DX_SCREEN_BACK);

	back *bk = new back();
	block *bl = new block();
	block stairs[6];
	player *pl = new player();
	scene *se = new scene();

	for (int i = 0; i < 3; i++)
	{
		stairs[i].set_x = 32 * i;
	}
	stairs[3].set_x = 32;
	stairs[3].set_y = -32;
	stairs[4].set_x = 32 * 2;
	stairs[4].set_y = -32 * 2;
	stairs[5].set_x = 32 * 2;
	stairs[5].set_y = -32;
	
	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();

		//タイトル画面
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
			//背景描画
			bk->drawPlay();

			//ブロック描画
			bl->All();
			//階段描画　後で書く場所変えるかも
			for (int i = 0; i < 6; i++)
			{
				stairs[i].All();
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					stairs[i].bl_x = 800;
				}
			}

			if (CheckHitKey(KEY_INPUT_0))
			{
				se->doTitlemode();
			}

			//プレイヤー描画
			pl->Draw();

		}

		ScreenFlip();
	}

	delete bk;
	delete bl;

	DxLib_End();



	return 0;

}