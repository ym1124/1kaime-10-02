#pragma once
enum { TITLE, PLAY, OVER, CLEAR };
class scene
{
public:
	int nowscene;
	int start_timer;
	bool start_flg;
	scene()
	{
		start_flg = false;
		start_timer = 0;
		nowscene = TITLE;
	}
	void doTitlemode();
	void doPlaymode();
};