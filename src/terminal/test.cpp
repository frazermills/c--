#include <terminal.h>

void init(){
    winmain = initscr();
    line = 10;
    int row,col;
    getmaxyx(winmain, row, col);
    maxLines = row;
    insert = true;
    frame = 0;
    refresh();

    start_color();
    init_color(BLACK, 100, 100, 100);
    init_color(YELLOW, 240*4, 226*4, 123*4);
    init_color(OFFWIHTE, 900, 900, 900);
    init_pair(1, OFFWIHTE, BLACK);
    wbkgd(winmain, COLOR_PAIR(1));

    nodelay(winmain, 1);

    initscr();
    noecho();
    keypad(winmain, TRUE);
}

void CleanUp(){
    endwin();
}

void SaveToFile(std::vector<int> text){
    std::ofstream File("code.txt", std::ios::out| std::ios::binary);
    
    int index = 0;
    int lines = 0;
    for (char c : text){
        // check if before or after line count
        if(c == 10){
            index = 0;
            File << std::endl;
            lines++;
        }
        else if(index > 3 + ((lines+1) / 10) && c != 0)
            File << c;
        index++;
    }
    File.close();
}

std::vector<int> PadLine(std::vector<int> text){
    std::string s = std::to_string(line);
    for(char cha : s){
        text.push_back(cha);
    }
    for(int i = 0; i < 2; i++){
        text.push_back(' ');
    }
    text.push_back(0);

    return text;
}

std::vector<int> HandleInput(std::vector<int> text, int c){
    // TODO: make not physicaly painful to look at
    if(c < 10)
        return text;

    if(c == '`'){
        insert = !insert;
        printw("Changed modes %d", insert);
        getch();
    }
    else if(insert){
        if((c == 127) || (c == 263)){
            if(text.size() > 5){
                if(text.back() == 0){
                    while (text.back() != 10)
                    {
                        text.pop_back();
                    }
                    line -= 10;
                }
                text.pop_back();
            }
        }
        else if (c == 16)
        {
            wclear(winmain);
            printw("Saving file... Enter to continue");
            SaveToFile(text);
            getch();
            wclear(winmain);
        }else if(c == 10){
            int row,col;
            getmaxyx(winmain, row, col);

            line += 10;
            text.push_back(c);

            text = PadLine(text);

        }else if(c == '\t'){
            for(int i = 0; i < 2; i++){
                text.push_back(' ');
            }
        }
        else{
            if((c > 96) && (c < 123))
                text.push_back(c - 32);
            else
                text.push_back(c);
        }
    }else{
        int x,y;
        getyx(winmain, x, y);
        wprintw(winmain, "%d %d" , y,x);
        switch (c)
        {
        case 'j':
            x--;
            break;
        case 'k':
            x++;
            break;
        case 'l':
            y++;
            break;
        case ';':
            y--;
            break;
        default:
            break;
        }
        wprintw(winmain, "%d %d" , y,x);
        wmove(winmain, 0, 0);
        wrefresh(winmain);
    }

    return text;
}

int main(int argc, char ** argv)
{
    init();
    int currentChar;
    std::vector<int> text;

    text = PadLine(text);

    while(true){
        frame++;
        refresh();

        wrefresh(winmain);
        wclear(winmain);

        int newLines = 0;
        int diff = (line - (maxLines * 10)) / 10;
        int linesPrinted = 0;
        int charCount = 0;

        for(int c : text){
            if(((maxLines * 10) < line) && (newLines < diff)){
                if(c == 10)
                    newLines++;
            }else{

                if((frame % 100 == 0) && linesPrinted == 0){
                    if(c == 10 || charCount == 0){
                        wprintw(winmain, "\n");
                    }
                }
                if(c == 10)
                    linesPrinted++;

                wprintw(winmain, "%c", c);
            }
            charCount++;
        }

        currentChar = wgetch(winmain);
        text = HandleInput(text, currentChar);
    }

    CleanUp();
    return 0;
}