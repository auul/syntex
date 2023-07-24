#include <syntex.h>

int main(void)
{
	if (WinInit()) {
		WinLoop();
		WinExit();
	}

	return 0;
}
