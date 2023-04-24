#include <iostream>

#define FISH 	1

using namespace std;

class Fish{
private:
	int y;
	int x;
	int score;

	WINDOW* w;


public:
	Fish() {}
	Fish(WINDOW* win, int y, int x) : w(win), y(y), x(x) {}

	void Print(int& y, int& x) 			/// NORMAL FISH
	{
		start_color();
		init_pair(FISH, COLOR_YELLOW, COLOR_BLACK);
		wattron(w, COLOR_PAIR(FISH));
		mvwprintw(w, y-1, x+2, "_");
		mvwprintw(w, y, x, "><_>");
	}


	///  _><_>

	void PrintRS(int& y, int& x) 		/// REVERSE FISH
	{
		start_color();
        init_pair(FISH, COLOR_YELLOW, COLOR_BLACK);
        wattron(w, COLOR_PAIR(FISH));
		mvwprintw(w, y-1, x+1, "_");
		mvwprintw(w, y, x, "<_><");
	}

	void PrintWH(int& y, int& x)		/// WHITE SPACE TO DELETE OBJS
	{
		mvwprintw(w, y-1, x+1, "  ");
		mvwprintw(w, y, x, "    ");
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


	// GENERATING FOOD.
	/// BUT IT SHOULD BE WITHOUT FUNCTION TO GET COORDINATES, SHIT.


	void Move(char& key, int& y, int& x, int& score, bool& inverse)
	{

		Fish F(w, y, x);

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
    	} /// CHEAT CODES:
        else if (key == 'p')
        {
            score += 500;
        }
		else if (key == 'l')
		{
			score -= 1000;
		}

	}



};
