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
	block stairs[6];//ŠK’i—p
	setStairs(stairs);
	pl->setPlayerPos();

	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();

		//ƒ^ƒCƒgƒ‹‰æ–Ê
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
			//”wŒi•`‰æ
			bk->drawPlay();

			//ƒuƒƒbƒN•`‰æ
			bl->All();
			//ŠK’i•`‰æ
			stairsAll(stairs,pl);
			if (pl->worldchange == 0)setStairs(stairs);
			if (pl->worldchange==1)setStairsMirror(stairs);//setŒn‚ð‰½‰ñ‚àŒÄ‚Ô‚Ì‚Í‚æ‚­‚È‚¢‚Ì‚ÅŒã‚Å•Ï‚¦‚é
			if (stairs[3].bl_x < 0)resetStairs(stairs);

			if (CheckHitKey(KEY_INPUT_0))
			{
				se->doTitlemode();
			}

			//ƒvƒŒƒCƒ„[•`‰æ
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