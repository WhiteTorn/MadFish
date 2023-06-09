    ///          https://github.com/WhiteTorn/MadFish
    #include <iostream>
    #include <ncurses.h>
    #include <cstdlib>
    #include <unistd.h>
    #include <vector>
    /// Creating Serios OOP

    #define MAIN_COLOR      1
    #define REVS_COLOR      2
    #define STAT_COLOR      3
    #define PLAY_COLOR      4
    #define FOOD_COLOR      5

    // fishs color.
    #define FISH_COLOR      6
    #define SMALL_COLOR     7
    #define BIG_COLOR       8
    #define SHARK_COLOR     9


    #define SMALL_NUM       3
    #define BIG_NUM         2


    #define RA(min,max)     ( (min) + rand() % ( (max) - (min) + 1) )

    using namespace std;

    void Sleep(int sec) { usleep(sec * 1000 * 1000); }



    /// FISH IS DONE.
    class Fish{
    private:
            int y;
            int x;
            int score = 0;
            bool inverse = false;

            WINDOW* w;


    public:
            Fish() {}
            Fish(WINDOW* win, int y, int x) {Init(w,y,x);}

            void Init(WINDOW* win, int yf, int xf)
            {
                    w = win;
                    y = yf;
                    x = xf;
            }

            void Print()                    /// NORMAL FISH
            {
                    start_color();
                    init_pair(FISH_COLOR, COLOR_YELLOW, COLOR_BLACK);
                    wattron(w, COLOR_PAIR(FISH_COLOR));
                    mvwprintw(w, y, x, "><'>");
                    wrefresh(w);
            }


            ///  _><_>

            void PrintRS()          /// REVERSE FISH
            {
                    start_color();
                    init_pair(FISH_COLOR, COLOR_YELLOW, COLOR_BLACK);
                    wattron(w, COLOR_PAIR(FISH_COLOR));
                    mvwprintw(w, y, x, "<'><");
                    wrefresh(w);
            }

            void PrintWH()          /// WHITE SPACE TO DELETE OBJS
            {
                    mvwprintw(w, y, x, "    ");
                    wrefresh(w);
            }

            void dispscore(WINDOW* w, int score)
            {
                    start_color();
                    init_pair(FISH_COLOR, COLOR_YELLOW, COLOR_BLACK);
                    wattron(w, COLOR_PAIR(FISH_COLOR));
                    mvwprintw(w, 3, 3, "SCORE: %4d",score);
                    wattroff(w, COLOR_PAIR(FISH_COLOR));
            }

            int Move(char key)
            {

                    PrintWH();

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
                    else if (key == 'o') /// WIN STATEMENT
                    {
                            score = 5521;
                            return 1;
                    }
                    Movo();
                    Inverse(key);
                    GetFood();
                    return 0;
            }

            void Movo(){
                    if (y < 0)
                    {
                            y = getmaxy(w) - 1;
                            score -= 1;
                    }
                    else if (y >= getmaxy(w))
                    {
                            y = 0;
                            score -= 1;
                    }
                    else if (x < 0)
                    {
                            x = getmaxx(w) - 1;
                            score -= 1;
                    }
                    else if (x >= getmaxx(w))
                    {
                            x = 0;
                            score -= 1;
                    }

            }

            void Inverse(char key)
            {
                    if (inverse)
                    {
                            if (key == 's' || key == 'w')
                            {
                                    PrintRS();
                            }
                            else { PrintRS(); }
                    }
                    else if (!inverse)
                    {
                            if (key == 's' || key == 'w')
                            {
                                    Print();
                            }
                            else { Print(); }
                    }
            }


            int rand_y[29], rand_x[29];


            void Food(int color)
            {
                    int max_y = getmaxy(w);
                    int max_x = getmaxx(w);
                    for (int i = 0; i < 29; i++)
                    {
                            rand_y[i] = rand() % (max_y - 2) + 1; // -2 and +1 to avoid borders
                            rand_x[i] = rand() % (max_x - 2) + 1;
                            wattron(w, COLOR_PAIR(color));
                            mvwprintw(w, rand_y[i], rand_x[i], "*");
                            wattroff(w, COLOR_PAIR(color));
                    }
            }

            void GetFood()
            {
                    for (int i = 0; i < 29; i++)
                    {
                            if (y == rand_y[i] && x + 3 == rand_x[i] && !inverse) {

                            score += 25;

                            mvwprintw(w, rand_y[i], rand_x[i], " ");


                            rand_y[i] = 0;
                            rand_x[i] = 0;
                            }
                            else if (y == rand_y[i] && x == rand_x[i] && inverse) {

                            score += 25;

                            mvwprintw(w, rand_y[i], rand_x[i], " ");


                            rand_y[i] = 0;
                            rand_x[i] = 0;
                            }
                    }
            }

            void EatFish()
            {
                score += 350;
            }

            void Eated()
            {
                score -= 300000;
            }

            void ZDefeat()
            {
                score = 5521;
            }


            //
            int getX() {return x;}
            int getY() {return y;}
            int getScore() {return score;}

    };


    class Small{
    protected:
            int sx;
            int sy;
            int dir;

        int min;
        int max;
        bool inverse = false;

        WINDOW* w;
    public:
            Small() {}
            Small(WINDOW* win, int y, int x, int d, int mn, int mx) {Init(w,sy,sx,dir,min,max);}

            void Init(WINDOW* win, int y, int x, int d, int mn, int mx)
            {
                    w = win;
                    sy = y;
                    sx = x;
                    dir = d;
                    min = mn;
                    max = mx;
            }


            void Move() // -1 left ; +1 right
            {
                    if (dir == -1)  {if (sx == min + 2) {dir = 1; inverse = false;} else sx -= 1;}
                    else if (dir == 1)    {if (sx + 7 == max - 3) {dir = -1; inverse = true;} else sx +=1;}
                    wrefresh(w);
            }

            void Print()
            {
                    if (inverse)
                    {
                            start_color();
                            init_pair(SMALL_COLOR, COLOR_MAGENTA, COLOR_BLACK);
                            wattron(w, COLOR_PAIR(SMALL_COLOR));
                            mvwprintw(w, sy, sx, "<*)))><");
                            wrefresh(w);
                    }
                    else if (!inverse)
                    {
                            start_color();
                            init_pair(SMALL_COLOR, COLOR_MAGENTA, COLOR_BLACK);
                            wattron(w, COLOR_PAIR(SMALL_COLOR));
                            mvwprintw(w, sy, sx, "><(((*>");
                            wrefresh(w);
                    }
            }

            void PrintWH()
            {
                    if (!inverse)
                    {
                            mvwprintw(w, sy, sx-1, "        ");
                            wrefresh(w);
                    }
                    else if (inverse)
                    {
                            mvwprintw(w, sy, sx+1, "        ");
                            wrefresh(w);
                    }
            }

            int getX() {return sx;}
            int getY() {return sy;}
            int getD() {return dir;}       /// TO ADD INVERSE PRINTING.

            int Detect(Fish& F)
            {
                    if (F.getY() == getY() && F.getX() == getX())
                    {
                            return 1;
                    }
                    return 0;
            }


            void Moving()
            {
                  Move();
                  PrintWH();
                  Print();
                  wrefresh(w);
            }

    };

    class Shark{
    private:
        int shy;
        int shx;

        WINDOW* w;

    public:
        Shark() {}
        Shark(WINDOW* win, int y, int x) {Init(w, shy, shx);}

        // INITIALISE SHARK
        void Init(WINDOW* win, int y, int x)
        {
            w = win;
            shy = y;
            shx = x;

        }

        // PRINT SHARK
        void Print()
        {
                start_color();
                init_pair(SHARK_COLOR, COLOR_BLUE, COLOR_BLACK);
                wattron(w, A_BOLD);
                wattron(w, COLOR_PAIR(SHARK_COLOR));
                mvwprintw(w, shy-2, shx, "      .      ");
                mvwprintw(w, shy-1, shx, "\\_____)\\_____");
                mvwprintw(w, shy, shx,   "/--v____ __`<");
                mvwprintw(w, shy+1, shx, "        )/   ");
                mvwprintw(w, shy+2, shx, "        '    ");
                wattroff(w, A_BOLD);
                wrefresh(w);
        }

        // DETECT IF IT INTERSECTS WITH FISH!
        int Detect(Fish& F)
        {
            if ((F.getY() == getY() && (F.getX() >= getX() && F.getX() <= getX() + 12)) || (F.getY() == getY() - 1 && (F.getX() >= getX() && F.getX() <= getX() + 12)) || (F.getY() == getY() - 2 && (F.getX() >= getX() && F.getX() <= getX() + 12)) || (F.getY() == getY() + 1 && (F.getX() >= getX() && F.getX() <= getX() + 12)) || (F.getY() == getY() + 2 && F.getX() == getX() + 8 ))
            {
                return 1;
            }
            return 0;
        }

        int getX() {return shx;}
        int getY() {return shy;}

    };


    class Story{
    private:
            int y;
            int x;

            WINDOW* w;


    public:
            Story() {}
            Story(WINDOW* win, int y, int x) {Init(w,y,x);}


            void Init(WINDOW* win, int ys, int xs)
            {
                    w = win;
                    y = ys;
                    x = xs;
            }
            /// 0 point
            void Before(WINDOW* w,int y, int x)
            {
                    mvwprintw(w, y, x+6, "  A long time ago, there was peace and bliss in the Kingdom of Ungu.");
                    mvwprintw(w, y+1, x+5, "But everything ended with the death of Ungu's heir.");

            }

            /// 60 point
            void Zakos(WINDOW* w,int y, int x)
            {

                    mvwprintw(w, y, x, "It all started when Ungu's heir was defeated in battle by an evil shark called Zako,");
                    mvwprintw(w, y+1, x, "and since then Zako has been wreaking havoc on Ungu's kingdom. ");
                    mvwprintw(w, y+2, x, "To this day, the fishes are still hungry, and they're fighting for survival.");

            }

            ///100 point
            void Legend(WINDOW* w,int y, int x)
            {

                    mvwprintw(w, y, x-3, "According to legend, the only one who can save the Kingdom of Ungu will be born in 900 AD,");
                    mvwprintw(w, y+1, x, "an orange fish awaited the successor");
                    mvwprintw(w, y+2, x, "Will the orange fish be reborn? Will the fish rise to defend his kingdom?");

            }


            ///200 point
            void Birth(WINDOW* w,int y, int x)
            {

                    mvwprintw(w, y, x+10, "In 900 AD");
                    mvwprintw(w, y+2, x-4, "the heir of Ungu was born, the only power that could save the kingdom: Dex of Ungu.");

            }


            ///300 point
            void Dexs(WINDOW* w,int y, int x)
            {

                    mvwprintw(w, y, x-9, "Dex was very small and helpless, but he had the spirit of a true warrior.");
                    mvwprintw(w, y+1, x-9, "Dex was not only wise but also courageous, and he did not spend time having fun like other fish.");
                    mvwprintw(w, y+2, x-9, "Dex's only concern was his kingdom. When the time came,");
                    mvwprintw(w, y+3, x-9, "Dex left the kingdom to hunt others and gather enough strength.");


            }

            /// max point
            void Won(WINDOW* w,int y, int x)
            {

                    mvwprintw(w, y, x, "He did not give up, and he grew stronger and bigger, and finally, Dex was ready. ");
                    mvwprintw(w, y+1, x, "After many tries, Dex won the battle. Dex is the faithful heir of Ungu.");
                    mvwprintw(w, y+2, x, "He gave the Ungunians peace and freedom that had been taken from them centuries ago.");

            }

            void TRUEKING(WINDOW* w,int y, int x)
            {
                    wattron(w, A_BOLD);
                    mvwprintw(w, y, x+5, "From now on, everyone in the Ungu kingdom will be free. ");
                    mvwprintw(w, y+2, x+5, "Dex is the true king of Ungu!");
                    mvwprintw(w, y+4, x+5, "Dex is the true heir and the power!");
                    wattroff(w, A_BOLD);
            }


            void ERASE(WINDOW* w, int y, int x)
            {
                    mvwprintw(w, y, x-9, "                                                                                                  ");
                    mvwprintw(w, y+1, x-9, "                                                                                                ");
                    mvwprintw(w, y+2, x-9, "                                                                                                ");
                    mvwprintw(w, y+3, x-9, "                                                                                                ");
                    mvwprintw(w, y+4, x-9, "                                                                                                ");
            }

            void STORYTELLER(WINDOW* w, int score)
            {
                    Story S(w, 2, 13);

            if (score <= 60)
                    {
                            S.Before(w,1,100);
                    }
                    else if (score <= 200)
                    {
                            S.ERASE(w,1, 100);
                            S.Zakos(w,1,100);
                    }
                    else if (score <= 500)
                    {
                            S.ERASE(w,1, 100);
                            S.Legend(w, 1, 100);
                    }
                    else if (score <= 1000)
                    {
                            S.ERASE(w,1, 100);
                            S.Birth(w, 1, 100);
                    }
                    else if (score <= 2000)
                    {
                            S.ERASE(w,1, 100);
                            S.Dexs(w, 1, 100);
                    }
                    else if (score <= 3000)
                    {
                            S.ERASE(w,1, 100);
                            S.Won(w, 1, 100);
                    }
            }
    };




    class Game{
    private:
            WINDOW *mainwin, *playwin, *status;
            Fish F;
            Shark Z;
            Story S;
            Small SM;
            Small SMA;
            Small SMB;
            Small SMC;
            Small SMD;
            vector<Small> SMS;
            char key;
    public:
            Game()
            {
                    if ( (mainwin = initscr()) == NULL) { printf("ERROR!\n"); exit(-1); }
                    noecho();
                    curs_set(0);
                    nodelay(mainwin, true);

                    srand(time(NULL));

                    start_color();
                    init_pair(MAIN_COLOR, COLOR_BLACK, COLOR_WHITE);
                    init_pair(STAT_COLOR, COLOR_RED, COLOR_BLACK);
                    init_pair(PLAY_COLOR, COLOR_BLUE, COLOR_BLACK);
                    init_pair(REVS_COLOR, COLOR_BLACK, COLOR_BLUE);
                    init_pair(FOOD_COLOR, COLOR_GREEN, COLOR_BLACK);
                    wattron(mainwin,COLOR_PAIR(MAIN_COLOR));
                    wrefresh(mainwin);

                    playwin = subwin(mainwin,LINES-11,COLS-1,1,1);
                    wattron(playwin,COLOR_PAIR(PLAY_COLOR));
                    box(playwin,0,0);
                    wrefresh(playwin);

                    status  = subwin(mainwin,10,COLS,LINES-10,0);
                    wattron(status,COLOR_PAIR(STAT_COLOR));
                    box(status,0,0);
                    wrefresh(status);

                    int max_y = getmaxy(playwin);
                    int max_x = getmaxx(playwin);



                    F.Init(playwin, 10, 15);
                    Z.Init(playwin, 5, 13);
                    S.Init(status, 2, 13);
                    SM.Init(playwin, RA(4, max_y), RA(10, max_x), 1, 0, max_x);
                    SMA.Init(playwin, RA(6, max_y), RA(10, max_x), 1, 0, max_x);
                    SMB.Init(playwin, RA(9, max_y), RA(10, max_x), 1, 0, max_x);
                    SMC.Init(playwin, RA(11, max_y), RA(11, max_x), 1, 0, max_x);
                    SMD.Init(playwin, RA(11, max_y), RA(11, max_x), 1, 0, max_x);

                    SMS.push_back(SM);
                    SMS.push_back(SMA);
                    SMS.push_back(SMB);
                    SMS.push_back(SMC);
                    SMS.push_back(SMD);


                    F.Food(FOOD_COLOR);

                    F.Print();
                    Z.Print();
                    F.dispscore(status, F.getScore());



                    wrefresh(playwin);
                    wrefresh(status);
                    wrefresh(mainwin);
            }

            int Read()
            {
                    key = wgetch(playwin);
                    if (key == 'q') return 1;
                    return 0;
            }

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

            char getKey() { return key;}

            void MainLoop()
            {
                    while( !Read() )
                    {
                            F.Move(getKey());
                            F.Inverse(getKey());
                            F.Movo();
                            F.GetFood();

                            for (int i = 0; i < SMS.size(); i++)
                            {
                                    SMS[i].Moving();

                                    if (F.getScore() > 300 && SMS[i].Detect(F))
                                    {
                                        SMS.erase(SMS.begin() + i);
                                        F.EatFish();
                                    }
                                    else if (F.getScore() < 300 && SMS[i].Detect(F))
                                    {
                                        GameOver(status);
                                        break;
                                        F.Eated();
                                    }

                            }

                            if (F.getScore() >= 2000 && Z.Detect(F))
                            {
                                F.ZDefeat();
                            }
                            else if (F.getScore() < 2000 && Z.Detect(F))
                            {
                                F.Eated();
                            }

                            F.dispscore(status, F.getScore());

                            S.STORYTELLER(status, F.getScore());

                            wrefresh(playwin);
                            wrefresh(status);

                            if (F.getScore() < 0)
                            {
                                    GameOver(status);
                                    break;
                            }
                            else if (F.getScore() == 5521)
                            {
                                    GameWon(status);
                                    break;
                            }
                    }
            }

            ~Game()
            {
                    delwin(mainwin);
                    endwin();
            }
    };


    int main()
    {
            srand(time(NULL));
            Game game;
            game.MainLoop();
            return EXIT_SUCCESS;
    }
