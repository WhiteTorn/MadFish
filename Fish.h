#include <iostream>

#define FISH    1

using namespace std;

class Fish{
private:
        int y;
        int x;
        int score;

        WINDOW* w;
// WTF

public:
        Fish() {}
        Fish(WINDOW* win, int y, int x) : w(win), y(y), x(x) {}

        void Print(int ly, int lx)                      /// NORMAL FISH
        {
                start_color();
                init_pair(FISH, COLOR_YELLOW, COLOR_BLACK);
                wattron(w, COLOR_PAIR(FISH));
                mvwprintw(w, ly-1, lx+2, "_");
                mvwprintw(w, ly, lx, "><_>");
        }


        ///  _><_>

        void PrintRS(int ly, int lx)            /// REVERSE FISH
        {
                start_color();
        init_pair(FISH, COLOR_YELLOW, COLOR_BLACK);
        wattron(w, COLOR_PAIR(FISH));
                mvwprintw(w, ly-1, lx+1, "_");
                mvwprintw(w, ly, lx, "<_><");
        }

        void PrintWH(int ly, int lx)            /// WHITE SPACE TO DELETE OBJS
        {
                mvwprintw(w, ly-1, lx+1, "  ");
                mvwprintw(w, ly, lx, "    ");
        }

        void position(WINDOW* w, int y, int x)
        { mvwprintw(w,2,3,"Postition: %2d(y) %2d(x)",y,x); }

        void dispscore(WINDOW* w, int score)
        {
                start_color();
                init_pair(FISH, COLOR_YELLOW, COLOR_BLACK);
                wattron(w, COLOR_PAIR(FISH));
                mvwprintw(w, 3, 3, "SCORE: %4d",score);
                wattroff(w, COLOR_PAIR(FISH));
        }
};
