#include <terminal.h>

void init(){
    winmain = initscr();
    line = 10;
    refresh();

    initscr();
    noecho();
    keypad(winmain, TRUE);
}

void CleanUp(){
    endwin();
}

void SaveToFile(std::vector<int> text){
    std::ofstream File("code.txt");
    
    for (char c : text){
        File << c;
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
    if((c == 127) || (c == 263)){
        if(text.size() > 4){
            if(text.back() == 0){
                while (true)
                {
                    if(text.back() == 10){
                        line -= 10;
                        break;
                    }
                    if(text.size() > 8)
                        text.pop_back();
                }
                
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
        line += 10;
        text.push_back(c);

        text = PadLine(text);

        // Move cursor
    }
    else
        text.push_back(c);

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
