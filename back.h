#pragma once

class back 
{
public:
	int titleback_gh,playback_gh;
	void drawTitle();
	void drawPlay();
	back()
	{
		titleback_gh = LoadGraph("Data/Image/BG_1.png", true);
		playback_gh = LoadGraph("Data/Image/BG_1.png", true);
	}
};
