#include "ncurses.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int main()
{
	const char* id = " #";
	srand(time(NULL));
	initscr();
	char curbuf[COLS][LINES];
	char newbuf[COLS][LINES];
	for(int i = 0; i < COLS; ++i)
	{
		for(int j = 0; j < LINES; ++j)
		{
			curbuf[i][j] = id[1 - (rand() % 2)];
		}
	}
	noecho();
	curs_set(0);
	while(1)
	{
		for(int i = 0; i < COLS; ++i)
		{
			for(int j = 0; j < LINES; ++j)
			{
				unsigned char ncount = 0;
				ncount += (curbuf[(i - 1) % COLS][(j - 1) % LINES] == id[1]);
				ncount += (curbuf[(i) % COLS][(j - 1) % LINES] == id[1]);
				ncount += (curbuf[(i + 1) % COLS][(j - 1) % LINES] == id[1]);
				ncount += (curbuf[(i - 1) % COLS][(j) % LINES] == id[1]);
				ncount += (curbuf[(i + 1) % COLS][(j) % LINES] == id[1]);
				ncount += (curbuf[(i - 1) % COLS][(j + 1) % LINES] == id[1]);
				ncount += (curbuf[(i) % COLS][(j + 1) % LINES] == id[1]);
				ncount += (curbuf[(i + 1) % COLS][(j + 1) % LINES] == id[1]);
				if(curbuf[i][j] == id[1])
				{
					if(ncount == 2 || ncount == 3)
					{
						newbuf[i][j] = id[1];
					}
					else
					{
						newbuf[i][j] = id[0];
					}
				}
				else
				{
					if(ncount == 3)
					{
						newbuf[i][j] = id[1];
					}
					else
					{
						newbuf[i][j] = id[0];
					}
				}
			}
		}
		for(int i = 0; i < COLS; ++i)
		{
			for(int j = 0; j < LINES; ++j)
			{
				curbuf[i][j] = newbuf[i][j];
				mvaddch(j, i, curbuf[i][j]);
			}
		}
		refresh();
		usleep(16666);
	}
	endwin();
	return 0;
}
