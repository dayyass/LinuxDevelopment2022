#include <stdlib.h>
#include <ncurses.h>

int CODE_LINES = 0, MAX_LINE_LENGTH = 0;
int length[1024];
char *buf[1024];

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }


void winshow(WINDOW *win, int start_row, int start_col)
{
    werase(win);
    wmove(win, 1, 0);

    for (int row = start_row; row < min(start_row + LINES - 6, CODE_LINES); ++row) {
        char *line = buf[row];
        wprintw(win, "  %*d: %.*s\n", 4, row + 1, COLS - 14, line + min(length[row], start_col));
    }

    box(win, 0, 0);
    wrefresh(win);
}

int main(int argc, char **argv)
{
    char *filename = argv[1];
    FILE *fp = fopen(filename,"r");

    for (int i = 0; i < 1024; ++i) {
        buf[i] = NULL;
        size_t size;
        if ((length[i] = (int) getline(buf + i, &size, fp)) < 0) {
            break;
        }
        if (length[i] > 0 && buf[i][length[i] - 1] == '\n') {
            buf[i][length[i] - 1] = '\0';
            --length[i];
        }
        ++CODE_LINES;
        MAX_LINE_LENGTH = max(MAX_LINE_LENGTH, length[i]);
    }

    fclose(fp);

    initscr();
    noecho();
    cbreak();
    set_escdelay(0);

    printw("File: %s", filename);
    refresh();

    WINDOW *win = newwin(LINES - 4, COLS - 4, 2, 2);
    keypad(win, TRUE);
    scrollok(win, TRUE);

    int c, cur_row = 0, cur_col = 0;
    winshow(win, cur_row, cur_col);

    while ((c = wgetch(win)) != 27) {
        switch (c) {
            case KEY_UP:
                --cur_row;
                break;
            case ' ':
            case KEY_DOWN:
                ++cur_row;
                break;
            case KEY_PPAGE:
                cur_row -= LINES - 6;
                break;
            case KEY_NPAGE:
                cur_row += LINES - 6;
                break;
            case KEY_LEFT:
                --cur_col;
                break;
            case KEY_RIGHT:
                ++cur_col;
                break;
            default:
                break;
        }

        cur_row = max(0, min(cur_row, CODE_LINES - 1));
        cur_col = max(0, min(cur_col, MAX_LINE_LENGTH - 1));

        winshow(win, cur_row, cur_col);
    }

    endwin();
    for (int i = 0; i < CODE_LINES; ++i) {
        free(buf[i]);
    }

    return 0;
}
