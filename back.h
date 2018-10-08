#pragma once
#include "DxLib.h"
class back 
{
public:
	int titleback_gh,playback_gh,cloud_gh,snow_gh;
	int snowanim_x = 0, snowanim_y = 0, animCnt = 0; 
	int move_x = 0;
	void drawTitle();
	void drawPlay();
	void drawSnow();
	void drawCloud();
	void drawLayerAll(int cnt);
	back()
	{
		titleback_gh = LoadGraph("Data/Image/BG.png", true);
		playback_gh = LoadGraph("Data/Image/BG.png", true);
		cloud_gh = LoadGraph("Data/Image/BG_cloud.png", true);
		snow_gh = LoadGraph("Data/Image/snow.png",true);
	}
};
