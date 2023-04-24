#include <iostream>

using namespace std;


class Story{
private:
        int y;
        int x;

        WINDOW* w;


public:
        Story() {}
        Story(WINDOW* win, int y, int x) : w(win), y(y), x(x) {}

        /// 0 point
        void Before(WINDOW* w,int y, int x)
        {
                wattron(w, A_BOLD);
                mvwprintw(w, y, x+6, "  A long time ago, there was peace and bliss in the Kingdom of Ungu.");
                mvwprintw(w, y+1, x+5, "But everything ended with the death of Ungu's heir.");
                wattroff(w, A_BOLD);
        }

        /// 60 point
        void Zakos(WINDOW* w,int y, int x)
        {
                wattron(w, A_BOLD);
                mvwprintw(w, y, x+6, "It all started when Ungu's heir was defeated in battle by an evil shark called Zako,");
                mvwprintw(w, y+1, x+5, "and since then Zako has been wreaking havoc on Ungu's kingdom. ");
                mvwprintw(w, y+2, x+5, "To this day, the fishes are still hungry, and they're fighting for survival.");
                wattroff(w, A_BOLD);
        }

        ///100 point
        void Legend(WINDOW* w,int y, int x)
        {
                wattron(w, A_BOLD);
                mvwprintw(w, y, x+6, "According to legend, the only one who can save the Kingdom of Ungu will be born in 900 AD,");
                mvwprintw(w, y+1, x+5, "an orange fish awaited the successor");
                mvwprintw(w, y+2, x+5, "Will the orange fish be reborn? Will the fish rise to defend his kingdom?");
                wattroff(w, A_BOLD);
        }


        ///200 point
        void Birth(WINDOW* w,int y, int x)
        {
                wattron(w, A_BOLD);
                mvwprintw(w, y, x+10, "In 900 AD");
                mvwprintw(w, y+2, x, "the heir of Ungu was born, the only power that could save the kingdom: Dex of Ungu.");
                wattroff(w, A_BOLD);
        }


        ///300 point
        void Dexs(WINDOW* w,int y, int x)
        {
                wattron(w, A_BOLD);
                mvwprintw(w, y, x, "Dex was very small and helpless, but he had the spirit of a true warrior.");
                mvwprintw(w, y+1, x, "Dex was not only wise but also courageous, and he did not spend time having fun like other fish.");
                mvwprintw(w, y+2, x, "Dex's only concern was his kingdom. When the time came,");
                mvwprintw(w, y+3, x, "Dex left the kingdom to hunt others and gather enough strength.");
                wattroff(w, A_BOLD);

        }

        /// max point
        void Won(WINDOW* w,int y, int x)
        {
                wattron(w, A_BOLD);
                mvwprintw(w, y, x+10, "He did not give up, and he grew stronger and bigger, and finally, Dex was ready. ");
                mvwprintw(w, y, x+10, "After many tries, Dex won the battle. Dex is the faithful heir of Ungu.");
                mvwprintw(w, y, x+10, "He gave the Ungunians peace and freedom that had been taken from them centuries ago.");
                wattroff(w, A_BOLD);
        }

        void TRUEKING(WINDOW* w,int y, int x)
        {


        }


};
