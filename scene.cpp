
#include "all.h"

void scene::doTitlemode()
{
	nowscene = TITLE;
}

void scene::doPlaymode()
{
	start_timer += 1;
	if (start_timer >= 120)
	{
		nowscene = PLAY;
		start_flg = false;
		start_timer = 0;
	}
}