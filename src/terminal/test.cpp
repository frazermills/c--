#include <terminal.h>
#include <math.h>

void init(){
    winmain = initscr();
    line = 10;
    int row,col;
    getmaxyx(winmain, row, col);
    maxLines = row;
    insert = true;
    frame = 0;
    leftPad = 8;
    xPos = leftPad;
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
    text.push_back('\t');
    text.push_back(0);

    return text;
}

std::vector<int> HandleInput(std::vector<int> text, int c){
    // TODO: make not physicaly painful to look at
    if(c < 10)
        return text;

    if(c == '`'){
        insert = !insert;
    }
    else if(insert){
        if((c == 127) || (c == 263)){
            if(text.size() > 3 + floor(line / 10)){
                if(text.back() == 0){
                    while (text.back() != 10)
                    {
                        text.pop_back();
                        xPos--;
                    }
                    line -= 10;
                    yPos--;
                }
                text.pop_back();
                xPos--;
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
            yPos += 1;
            xPos = 8;

        }else if(c == '\t'){
            for(int i = 0; i < 2; i++){
                text.push_back(' ');
            }
            xPos+=2;
        }
        else{
            if((c > 96) && (c < 123))
                text.push_back(c);
            else
                text.push_back(c);
            xPos++;
        }
    }else{
        switch (c)
        {
        case 'h':
            xPos--;
            break;
        case 'j':
            yPos++;
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
        
        if(xPos < leftPad)
            xPos = leftPad;
        if(yPos <= 0)
            yPos = 0;
        if(yPos >= (line / 10) - 1)
            yPos = (line / 10) - 1;
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

                // screen jitter of beacause its a pain
                /*
                if((frame % 100 == 0) && linesPrinted == 0){
                    if(c == 10 || charCount == 0){
                        //wprintw(winmain, "\n");
                    }
                }
                */
                if(c == 10)
                    linesPrinted++;

                wprintw(winmain, "%c", c);
            }
            charCount++;
        }

        wmove(winmain, yPos, xPos);
        wrefresh(winmain);

        if(frame > 10000)
            frame /= 100;
        currentChar = wgetch(winmain);
        text = HandleInput(text, currentChar);
    }

    CleanUp();
    return 0;
}