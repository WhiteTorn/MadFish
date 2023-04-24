#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include "Fish.h"
#include "Story.h"
#include "Enemies.h"



using namespace std;

#define MAIN_COLOR      1
#define REVS_COLOR      2
#define STAT_COLOR      3
#define PLAY_COLOR      4
#define FOOD_COLOR      5


void Sleep(int sec) { usleep(sec * 1000 * 1000); }

void Clean(WINDOW* status)
{
        for(int i = 1; i <= 3; i++)
        {
                string emp(COLS-2,' ');
                mvwprintw(status,i,1,"%s",emp.c_str());
        }
}

void GameOver(WINDOW* w)
{
        Clean(w);
        wattron(w, A_BOLD);
        mvwprintw(w, 1, 100, "!YOU LOSE!");
        mvwprintw(w, 3, 100, "NO DEX, NOOOOOOOOO!");
        wattroff(w, A_BOLD);
        wrefresh(w);
        Sleep(3);
}
void GameWon(WINDOW* w)
{
        Clean(w);
        wattron(w, A_BOLD);
        mvwprintw(w, 1, 100, "From now on, everyone in the Ungu kingdom will be free. ");
        mvwprintw(w, 3, 100, "Dex is the true king of Ungu!");
        mvwprintw(w, 5, 100, "Dex is the true heir and the power!");
        wattroff(w, A_BOLD);
        wrefresh(w);
        Sleep(5);
}


int main()
{
        // WINDOW part
        WINDOW *mainwin;

        mainwin = initscr();    // initliazzation of screen
        curs_set(0);            // do not show the cursor
        noecho();               // do not print anything after key pressed

        srand(time(NULL));

        start_color();
        init_pair(MAIN_COLOR, COLOR_BLACK, COLOR_WHITE);
        init_pair(STAT_COLOR, COLOR_RED, COLOR_BLACK);
        init_pair(PLAY_COLOR, COLOR_BLUE, COLOR_BLACK);
        init_pair(REVS_COLOR, COLOR_BLACK, COLOR_BLUE);
        init_pair(FOOD_COLOR, COLOR_GREEN, COLOR_BLACK);
        wattron(mainwin,COLOR_PAIR(MAIN_COLOR));
        wrefresh(mainwin);

	WINDOW *status;
        status  = subwin(mainwin,10,COLS,LINES-10,0);
        wattron(status,COLOR_PAIR(STAT_COLOR));
        box(status,0,0);
        wrefresh(status);

        WINDOW *playwin;
        playwin = subwin(mainwin,LINES-11,COLS-1,1,1);

	/// CENTER COORDINATES
	int x = 20;
	int y = 10;
	char key;
	bool inverse = false;
        wattron(playwin,COLOR_PAIR(PLAY_COLOR));
        box(playwin,0,0);
        wrefresh(playwin);



	// PRINTING FISH
	Fish F(playwin, y, x);
        Story S(status, 2, 13);
        Small SM(playwin, 3, 70, y, x);
        Small SM2(playwin, 7, 90, y, x);
        Small SM3(playwin, 10, 110, y, x);

        int score = 0;


        F.position(status,y,x);
        F.dispscore(status, score);


        // FOODING
        // TODO CHANGE COLOUR
        int rand_y[14], rand_x[14];
        int max_y = getmaxy(playwin);
	int max_x = getmaxx(playwin);
        for (int i = 0; i < 14; i++)
	{
        	rand_y[i] = rand() % (max_y - 2) + 1; // -2 and +1 to avoid borders
        	rand_x[i] = rand() % (max_x - 2) + 1;
                wattron(playwin, COLOR_PAIR(FOOD_COLOR));
        	mvwprintw(playwin, rand_y[i], rand_x[i], "*");
                wattroff(playwin, COLOR_PAIR(FOOD_COLOR));
    	}

        wrefresh(playwin);
        wrefresh(status);
        wrefresh(mainwin);

	while (1)
	{
		key = wgetch(playwin);  // wait for key pressed: BLOCKING

                if (key == 'q')
                {
                        break;
                }

                F.Move(key, y, x, score, inverse);
                wattron(playwin,COLOR_PAIR(PLAY_COLOR));
                SM.Print();
                SM2.Print();
                SM3.Print();



                /// ETERNAL MIRROR
                if (y < 0)
                {
                        y = getmaxy(playwin) - 1;
                        score -= 1;
                }
                else if (y >= getmaxy(playwin))
                {
                        y = 0;
                        score -= 1;
                }
                else if (x < 0)
                {
                        x = getmaxx(playwin) - 1;
                        score -= 1;
                }
                else if (x >= getmaxx(playwin))
                {
                        x = 0;
                        score -= 1;
                }


                /// INVERSING FISH
		if (inverse)
		{
			if (key == 's' || key == 'w')
			{
				F.PrintRS(y,x);
			}
			else { F.PrintRS(y,x); }
		}
		else if (!inverse)
		{
			if (key == 's' || key == 'w')
			{
				F.Print(y,x);
			}
			else { F.Print(y,x); }
		}



                /// GETTING SCORES

                for (int i = 0; i < 14; i++)
                {
                        if (y == rand_y[i] && x == rand_x[i]) {
                // increment the score and print it at the top of the screen
                        score += 25;


                // remove the * character from the screen
                        mvwprintw(playwin, rand_y[i], rand_x[i], " ");

                        // REMOVE FROM ARRAY.
                        rand_y[i] = 0;
                        rand_x[i] = 0;
                        }
                }





                // IF X AND Y EQUALS TO FOOD X AND Y THAN SCORE ++

                F.position(status,y,x);
                F.dispscore(status, score);



                S.STORYTELLER(status, score);



                //S.Zakos(status,1,190);
                /// TODO CLEAR EVERYTHING WHAT WAS TYPED.

                wrefresh(playwin);
                wrefresh(status);     // send from MEMORY -> SCREEN



                if (score < 0)
                {
                        GameOver(status);
                        break;
                }
                else if (score == 5521)
                {
                        GameWon(status);
                        break;
                }
	}

	wrefresh(playwin);
        wrefresh(status);
        wrefresh(mainwin);


        delwin(mainwin);        // remove from MEMORY - WINDOW data structure
        endwin();               // clean up

        return EXIT_SUCCESS;
}
