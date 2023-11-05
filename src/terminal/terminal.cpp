#include <terminal.h>
#include <array>
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <math.h>

// TO RUN INSTALL NCURSES
// THEN DO g++ terminal.cpp -lncurses -I . && ./a.out

void init(){
    winmain = initscr();
    line = 1;
    int row,col;
    getmaxyx(winmain, row, col);

    MaxLineLength = col - (col / 4) - 4;
    maxLines = row;
    insert = true;
    frame = 0;
    leftPad = 8;
    xPos = 0;
    yPos = 0;
    refresh();

    start_color();
    init_color(BLACK, 100, 100, 100);
    init_color(YELLOW, 240*4, 226*4, 123*4);
    init_color(OFFWIHTE, 900, 900, 900);
    init_pair(1, OFFWIHTE, BLACK);
    wbkgd(winmain, COLOR_PAIR(1));

    attron(A_BOLD);

    initscr();
    noecho();
    keypad(winmain, TRUE);
}

void CleanUp(){
    endwin();
}


std::string GetStringInput(){
    wmove(winmain, maxLines-1,0);
    std::string input;

    int ch = getch();

    while (ch != '\n')
    {
        refresh();
        wrefresh(winmain);
        wclear(winmain);

        wmove(winmain, maxLines-1,0);
        if(ch == 263 && input.length() > 0)
            input.pop_back();
        else if(ch != 263)
            input.push_back(ch);

        wprintw(winmain, "Enter file name: ");

        for(auto c : input)
            wprintw(winmain, "%c", c);

        ch = getch();
    }

    return input;
}

void SaveToFile(std::array<std::array<int, 80>, 1000> text){

    std::string fileName = GetStringInput();

    std::ofstream File(fileName, std::ios::out| std::ios::binary);
    
    int index = 0;
    int lines = 0;
    for (auto charLine : text){
        for (char c : charLine){
            // check if before or after line count
            if((index > 5 + ((lines+1) / 10)) && (c != '@') && (c != 0) && (c != '$'))
                File << c;
            index++;
        }
        index = 0;
        lines++;
    }
    File.close();
}

std::array<std::array<int, 80>, 1000> PadLine(std::array<std::array<int, 80>, 1000> text){
    std::string s = std::to_string(line * 10);
    for(char cha : s){
        text[yPos][xPos++] = cha;
    }
    text[yPos][xPos++] = ' ';
    text[yPos][xPos++] = ' ';
    text[yPos][xPos++] = ' ';
    text[yPos][xPos++] = ' ';
    text[yPos][xPos++] = '$';

    return text;
}

std::array<std::array<int, 80>, 1000> ZeroArray(std::array<std::array<int, 80>, 1000> arr){
    for(int i = 0; i < 1000; i++){
        for(int j = 0 ; j < 80; j++)
            arr[i][j] = '@';
    }

    return arr;
}

void ExcuteCode(std::string str, std::array<std::array<int, 80>, 1000> text){

    SaveToFile(text);

    // DRAW VERTICAL BOX
    while(true){
        for(int y = 0 ; y < maxLines; y++){
            wmove(winmain, y, (col - col / 4) - 1);
            wprintw(winmain, "|");
        }
        wmove(winmain, 0, (col - col / 4));

        // Read output file and display here

        getch();
    }
}

std::array<std::array<int, 80>, 1000> OpenFile(std::array<std::array<int, 80>, 1000> text){
    text = ZeroArray(text);

    std::string codeLine;

    xPos = 0;
    yPos = 0;
    line = 1;

    std::string fileName = GetStringInput();

    std::ifstream CodeFile(fileName);

    while (getline(CodeFile, codeLine))
    {
        xPos = 0;
        text = PadLine(text);

        int charCount = 0;
        for(auto c : codeLine){
            text[yPos][xPos++] = c;
        }   
        text[yPos][xPos++] = '\n';

        line++;
        yPos++;
    }
    xPos = 0;
    text = PadLine(text);
    CodeFile.close();

    return text;
}


std::array<std::array<int, 80>, 1000> HandleInput(std::array<std::array<int, 80>, 1000> text, int c){
    // TODO: make not physicaly painful to look at
    int lastX = xPos - 1;
    if(c < 8)
        return text;

    else if(c == '`'){
        firstJ = true;
        firstk = true;
        insert = !insert;
    }
    else if(!insert){
        switch (c)
        {
        case 'h':
            xPos--;
            break;
        case 'j':
            if(text[yPos][0] == '@'){
                yPos--;
                text[yPos++][xPos] = '\n';
                line++;
                xPos = 0;
                text = PadLine(text);
            }else{
                yPos += 1;
            }
            firstJ = false;
            break;
        case 'k':
            yPos--;
            break;
        case 'l':
            xPos++;
            break;
        default:
            break;
        }
    }
    else if(insert){
        switch (c)
        {
            //Backspace
        case 263:
            if(text[yPos][lastX] == '$'){
                if(yPos != 0){
                    for(int i = xPos; i >= 0; i--){
                        text[yPos][i] = '@';
                    }
                    yPos--;
                    line--;

                    //find last char pos of new line
                    int lastIndex = 8;
                    int currentIndex = 0;
                    for(char character : text[yPos]){
                        if(character != '@' && currentIndex > lastIndex){
                            lastIndex = currentIndex;
                        }

                        currentIndex++;
                    }
                    xPos = lastIndex;
                }
            }else{
                text[yPos][--xPos] = '@';
            }
            
            // more checks needed
            break;
        case 11:
            ExcuteCode(GetStringInput() ,text);
            break;
        case 12:
            // open file
            text = OpenFile(text);
            break;
        case 16:
            wclear(winmain);
            printw("Saving file... Enter to continue");
            SaveToFile(text);
            getch();
            wclear(winmain);
            break;
        case 10:
            line += 1;
            text[yPos++][xPos] = '\n';
            xPos = 0;            

            text = PadLine(text);
            break;
        case '\t':
            for(int i = 0; i < 2; i++){
                text[yPos][xPos++] = ' ';
            }
            break;
        
        default:
            if(xPos < MaxLineLength)
                text[yPos][xPos++] = c;
            break;
        }
    }

    return text;
}

int main(int argc, char **argv)
{
    init();
    int currentChar;
    std::array<std::array<int, 80>, 1000> text;

    text = ZeroArray(text);
    text = PadLine(text);

    while(true){
        frame++;
        refresh();

        wrefresh(winmain);
        wclear(winmain);


        getmaxyx(winmain, row, col);
        maxLines = row;

        int newLines = 0;
        int diff = line - maxLines;
        int linesPrinted = 0;
        int charCount = 0;

        wmove(winmain, 0, 0);
        for(auto charLine : text){
            if(diff > 0){
                diff--;
            }else{
                for(int c : charLine){
                    if(c != '@' && c != '$')
                        wprintw(winmain, "%c", c);
                }
            }
        }

        wmove(winmain, yPos, xPos-1);


        currentChar = wgetch(winmain);
        text = HandleInput(text, currentChar);
    }

    CleanUp();
    return 0;
}