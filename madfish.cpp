#include <iostream>
#include <ncurses.h>
#include "Fish.h"
#include "Story.h"


using namespace std;

#define MAIN_COLOR      1
#define REVS_COLOR      2
#define STAT_COLOR      3
#define PLAY_COLOR      4




int main()
{
        // WINDOW part
        WINDOW *mainwin;

        mainwin = initscr();    // initliazzation of screen
        curs_set(0);            // do not show the cursor
        noecho();               // do not print anything after key pressed

        start_color();
        init_pair(MAIN_COLOR, COLOR_BLACK, COLOR_WHITE);
        init_pair(STAT_COLOR, COLOR_RED, COLOR_BLACK);
        init_pair(PLAY_COLOR, COLOR_BLUE, COLOR_BLACK);
        init_pair(REVS_COLOR, COLOR_BLACK, COLOR_BLUE);
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

        int score = 500;

        F.position(status,y,x);
        F.dispscore(status, score);

        wrefresh(playwin);
        wrefresh(status);
        wrefresh(mainwin);

        while (1)
        {
                key = wgetch(playwin);  // wait for key pressed: BLOCKING
//                wattron(playwin,COLOR_PAIR(REVS_COLOR));
                F.PrintWH(y,x);

                if (key == 'a') // LEFT
                {
                        x-=1;
                        inverse = true;
                }
                else if (key == 's') // DOWN
                {
                        y+=1;
                }
                else if (key == 'w') // UP
                {
                        y-=1;
                }
                else if (key == 'd') // RIGHT
                {
                        x+=1;
                        inverse = false;
                }
                else if (key == 'q')
                {
                        break;
                }
                wattron(playwin,COLOR_PAIR(PLAY_COLOR));

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

                // IF X AND Y EQUALS TO FOOD X AND Y THAN SCORE ++

                F.position(status,y,x);
                F.dispscore(status, score);
                S.Before(status,1,100);
                //S.Zakos(status,1,190);
                /// TODO CLEAR EVERYTHING WHAT WAS TYPED.

                wrefresh(playwin);
                wrefresh(status);     // send from MEMORY -> SCREEN
        }

        wrefresh(playwin);
        wrefresh(status);
        wrefresh(mainwin);


        delwin(mainwin);        // remove from MEMORY - WINDOW data structure
        endwin();               // clean up

        return EXIT_SUCCESS;
}

