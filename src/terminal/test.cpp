#include <terminal.h>

void init(){
    winmain = initscr();
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

int main(int argc, char ** argv)
{
    init();
    int currentChar;
    std::vector<int> text;

    while(true){
        currentChar = wgetch(winmain);
        wclear(winmain);

        if((currentChar == 127) || (currentChar == 263)){
            if(text.size() > 0)
                text.pop_back();
        }
        else if (currentChar == 16)
        {
            wclear(winmain);
            printw("Saving file... Enter to continue");
            SaveToFile(text);
            getch();
            wclear(winmain);
        }
        else
            text.push_back(currentChar);


        for(int c : text){
            wprintw(winmain, "%c", c);
        }
    }

    CleanUp();
    return 0;
}
