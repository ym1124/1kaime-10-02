#include "controller.h"

void debugController(int pad)
{
	for (int i = 0; i < 28; i++)
	{
		if (pad&(1 << i))
		{
			DrawFormatString(0, i * 15, GetColor(100, 155, 155), "%d‚ð“ü—Í’†‚Å‚·", i);
		}
	}
}