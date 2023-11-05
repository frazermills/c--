#include <terminal.h>
#include <array>
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <math.h>

void init(){
    winmain = initscr();
    line = 1;
    int row,col;
    getmaxyx(winmain, row, col);
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

    //nodelay(winmain, 1);
    attron(A_BOLD);
    //attron(A_STANDOUT);

    initscr();
    noecho();
    keypad(winmain, TRUE);
}

void CleanUp(){
    endwin();
}

void SaveToFile(std::array<std::array<int, 80>, 1000> text){
    std::ofstream File("code.txt", std::ios::out| std::ios::binary);
    
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

std::string GetStringInput(){
    wmove(winmain, maxLines-1,0);
    echo();
    wprintw(winmain, "Enter file name: ");
    std::string input;

    int ch = getch();

    while ( ch != '\n' )
    {
        input.push_back(ch);
        ch = getch();
    }
    noecho();

    return input;
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
    if(c < 10)
        return text;

    if(c == '`'){
        firstJ = true;
        insert = !insert;
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
                            //printw("%d", character);
                            //getch();
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
            text[yPos][xPos++] = c;
            break;
        }
    }else{
        switch (c)
        {
        case 'h':
            xPos--;
            break;
        case 'j':
            yPos += 1;
            if(text[yPos][0] == '@'){
                text[yPos++][xPos] = '\n';
                line++;
                xPos = 0;
                text = PadLine(text);
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


        int row,col;
        getmaxyx(winmain, row, col);
        maxLines = row;

        int newLines = 0;
        int diff = line - maxLines;
        int linesPrinted = 0;
        int charCount = 0;

        for(auto charLine : text){

            for(int c : charLine){
                if(diff > 0){
                    diff--;
                    break;
                }

                if(c != '@' && c != '$')
                    wprintw(winmain, "%c", c);
            }
        }

        wmove(winmain, yPos, xPos-1);
        wrefresh(winmain);

        currentChar = wgetch(winmain);
        text = HandleInput(text, currentChar);
    }

    CleanUp();
    return 0;
}