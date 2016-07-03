#include <ncurses.h>

int main(int argc, char *argv[])
{
    int ch,c;
    initscr();
    cbreak();
    noecho();

    while( ch != 'q')
    {
        switch( c = getch() )
        {
            case 'a':
                ch = 'b';
            break;

            case 'b':
                ch = 'c';
            break;

            case 'c':
                ch = 'd';
            break;

            default:
                ch = c;                 
            break;
        }
        printw("%c",ch);
    }
    endwin();
    return(0);
}