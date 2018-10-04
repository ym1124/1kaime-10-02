#include"all.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{

	ChangeWindowMode(true);

	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

	DxLib_Init();

	SetDrawScreen(DX_SCREEN_BACK);

	back *bk = new back();
	player *pl = new player();
	scene *se = new scene();
	pl->setPlayerPos();

	int cnt = -1,color=GetColor(150,155,155);
	//�K�i�p******************************************
	block stairs[6];//bl_x��������bl_y	�������ύX�����C���X�^���X���ŏ��ɂł���̂ŏ����l�͑傫�����Ă���(-���ƃ��[�v���Ă���)
	block stairs1[6];
	//***********************************************
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
			cnt++;
			//�w�i�`��
			bk->drawPlay();
			//�K�i�ݒ�
			//******************************
			setStairsAll(100, cnt,BLACK_WORLD ,stairs);
			setStairsAll(700, cnt,WHITE_WORLD, stairs1);
			//******************************
			if (CheckHitKey(KEY_INPUT_0))
			{
				se->doTitlemode();
			}
			//�v���C���[�`��
			pl->setPlayerPos();
			pl->Jump();
			pl->Draw();
		}
		DrawFormatString(30, 30, color, "cnt:%d", cnt);

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