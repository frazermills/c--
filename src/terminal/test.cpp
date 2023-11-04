#include <terminal.h>

void init(){
    winmain = initscr();
    line = 10;
    refresh();

    start_color();
    init_color(9, 100, 100, 100);
    init_color(10, 240*4, 226*4, 123*4);
    init_pair(1, YELLOW, BLACK);
    wbkgd(winmain, COLOR_PAIR(1));

    initscr();
    noecho();
    keypad(winmain, TRUE);
}

void CleanUp(){
    endwin();
}

void SaveToFile(std::vector<int> text){
    std::ofstream File("code.txt");
    
    int index = 0;
    for (char c : text){
        // check if before or after line count
        if(c == 10)
            index = 0;
        if(index > 3)
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
    text.push_back('\t');
    text.push_back(0);

    return text;
}

std::vector<int> HandleInput(std::vector<int> text, int c){
    // TODO: make not physicaly painful to look at
    if((c == 127) || (c == 263)){
        if(text.size() > 4){
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

        if((row * 10) > line){
            line += 10;
            text.push_back(c);

            text = PadLine(text);
        }

    }
    else{
        if((c > 96) && (c < 123))
            text.push_back(c - 32);
        else
            text.push_back(c);
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
        refresh();

        wrefresh(winmain);
        wclear(winmain);


        for(int c : text){
            wprintw(winmain, "%c", c);
        }
        currentChar = wgetch(winmain);
        text = HandleInput(text, currentChar);
    }

    CleanUp();
    return 0;
}
