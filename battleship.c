//uncomment one of these includes depending on the computer you're using
//(add one if you have something different)
//#include <ncurses/ncurses.h> //lab computers
#include <curses.h> //corbin's laptop
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <Windows.h>
//uncomment one of these includes depending on the computer you're using
//(add one if you have something different)
//#include <ncurses/ncurses.h> //lab computers
#include<curses.h> //corbin's laptop

#define BOARD_LENGTH 10
#define BOARD_WIDTH 10
#define SHIP_CHAR '$'
#define SHIP_HIT 'X'
#define SHIP_MISS '0'
#define BLANK '*'
//structs are used to check if parts of the boats are hit.
//using int {varible} = 1 or 0 depending if it is true or false
struct carrier
{
    int points[3][2];
};

struct patrol
{
    int points[2][2];
};

struct boat
{
    int points[1][2];
};

struct ships
{
    struct carrier c;
    struct patrol p;
    struct boat b;
};

void draw_character(int row, int column, char use)
{
    mvaddch(row, column, use);
    refresh();
}

void draw_string(int row, int column, char *string){
    mvprintw(row, column, string);
    refresh();
}

void displayCurrentBoard(int gridData[BOARD_LENGTH][BOARD_WIDTH], int x, int y)
{
    /*
    board looks like
    $ = ship
    X = ship hit
    O = misses from other player
    P = position of x and y (for testing)
 P  1 2 3 4 5 6 7 8 9 10
    --------------------
 A | * * * * * * * * * *
 B | * * * * * * * * * *
 C | * * * * * * * * * *
 D | * * * * * * * * * *
 E | * * * * * * * * * *
 F | * * * * * * * * * *
 G | * * * * * * * * * *
 H | * * * * * * * * * *
 I | * * * * * * * * * *
 J | * * * * * * * * * *
    */

    char tmp = 'P'; //placeholder representing starting reference location
    draw_character(y,x,tmp); //can take out later
    
    //print border info
    char *temp1 = "1 2 3 4 5 6 7 8 9 10";
	char *temp2 = "--------------------";
    draw_string(y, x + 3,temp1);
    draw_string(y + 1, x + 3,temp2);

    char *temp3 = " |";

    char displayChar = BLANK;

    //display everything inside border
    for(int i = 0; i < BOARD_LENGTH; i++){
        draw_character(y+2+i,x,65+i);       //print A, B, C, etc
        draw_string(y+2+i,x+1,temp3);       //print " |"
		for (int j = 0; j < BOARD_WIDTH; j++) {
	        //print information based on arrays
            //switch to detect current value to print
            switch(gridData[i][j]){
                case 0:
                    displayChar = BLANK;
                    break;
                case 1:
                    displayChar = SHIP_CHAR;
                    break;
                case 2:
                    displayChar = SHIP_HIT;
                    break;
                case 3:
                    displayChar = SHIP_MISS;
                    break;
                default:
                printf("ERROR IN gridData");
            }
            draw_character(y+2+i,x+4+j*2,displayChar); //draw switched character
		}       
    }
}

void placeShips(int *gridData, struct carrier c, struct patrol p, struct boat b)
{
    //Starting ship placement at [0][0]
    //int x = 0 y = 0;
    /*
	
    //moving the ships on keypress are hopefully FINISHED
    //Still need to check if the ships are on top of each other.
    (The current numbers(0,7,9) are trying to be the limits of the 10x10 board)
    //place carrier while loop
    while (1){
        int ch = getch();
        if (ch == 'w'){
            if(y == 0){
                y = 7;
                
                gridData[0][x] = '*';
                gridData[1][x] = '*';
                gridData[2][x] = '*';
            }
            else{
                gridData[y][x] = '*';
                gridData[y+1][x] = '*';
                gridData[y+2][x] = "*";
                y--;
        
            }
        }
        else if (ch == 's'){
            if (y == 7){
                y = 0;
                
                gridData[7][x] = '*';
                gridData[8][x] = '*';
                gridData[9][x] = '*';
            }
            else{
                gridData[y][x] = '*';
                gridData[y+1][x] = '*';
                gridData[y+2][x] = "*";
                y++;
                
            }
        }
        else if (ch == 'd'){
            if (x == 9){
                x = 0;
                
                gridData[y][9] = '*';
                gridData[y+1][9] = '*';
                gridData[y+2][9] = '*';
            }
            else{
                gridData[y][x] = '*';
                gridData[y+1][x] = '*';
                gridData[y+2][x] = "*";;
                x++;
                
            }
        }
        else if (ch == 'a'){
            if (x == 0){
                x = 9;
                
                gridData[y][0] = '*';
                gridData[y+1][0] = '*';
                gridData[y+2][0] = '*';
            }
            else{
                gridData[y][x] = '*';
                gridData[y+1][x] = '*';
                gridData[y+2][x] = "*";
                x--
                
            }
        }
        else if (ch == 'k'){
            
            break;
        }
    c.points[0] = {x,y};
	c.points[1] = {x,y+1};
    c.points[2] = {x,y+2};
    gridData[y][x] = shipChar;
    gridData[y+1][x] = shipChar;
    gridData[y+2][x] = shipChar;
    displayCurrentBoard(gridData);
    }
    if(gridData[0][0] == shipChar && gridData[1][0] == shipChar){
        x = 1;
        y = 0;
    }
    else{
        x = 0;
        y = 0;
    }
    //patrol while loop
    while (1){
        int ch = getch();
        if (ch == 'w'){
            if(y == 0){
                y = 7;
                
                gridData[0][x] = '*';
                gridData[1][x] = '*';
            }
            else{
                gridData[y][x] = '*';
                gridData[y+1][x] = '*';
                y--;
                
            }
        }
        else if (ch == 's'){
            if (y == 7){
                y = 0;
                
                gridData[7][x] = '*';
                gridData[8][x] = '*';
            }
            else{
                gridData[y][x] = '*';
                gridData[y+1][x] = '*';
                y++;
                
            }
        }
        else if (ch == 'd'){
            if (x == 9){
                x = 0;
                
                gridData[y][9] = '*';
                gridData[y+1][9] = '*';
            }
            else{
                gridData[y][x] = '*';
                gridData[y+1][x] = '*';
                x++;
                
            }
        }
        else if (ch == 'a'){
            if (x == 0){
                x = 9;
                
                gridData[y][0] = '*';
                gridData[y+1][0] = '*';
            }
            else{
                gridData[y][x] = '*';
                gridData[y+1][x] = '*'; 
                x--
                
            }
        }
        else if (ch == 'k'){
            
            break;
        }
    p.points[0] = {x,y};
	p.points[1] = {x,y+1};
    gridData[y][x] = shipChar;
    gridData[y+1][x] = shipChar;
    displayCurrentBoard(gridData);
    }
    y = 0;
    if(gridData[0][0] == shipChar){
        if(gridData[0][1] == shipChar){
            x = 2;
        }
        else{
            x = 1;
        }
        
    }
    else{
        x = 0;
    }
    //boat while loop
    while (1){
        int ch = getch();
        if (ch == 'w'){
            if(y == 0){
                y = 7;
                gridData[0][x] = '*';
            }
            else{
                gridData[y][x] = '*';
                y--;
            }
        }
        else if (ch == 's'){
            if (y == 7){
                y = 0;
                gridData[7][x] = '*';
            }
            else{
                gridData[y][x] = '*';;
                y++;
            }
        }
        else if (ch == 'd'){
            if (x == 9){
                x = 0;
                gridData[y][9] = '*';
            }
            else{
                gridData[y][x] = '*';
                x++;
            }
        }
        else if (ch == 'a'){
            if (x == 0){
                x = 9;
                
                gridData[y][0] = '*';
            }
            else{
                gridData[y][x] = '*';
                x--
                
            }
        }
        else if (ch == 'k'){
            break;
        }
    b.points[0] = {x,y};
    gridData[y][x] = shipChar;
    displayCurrentBoard(gridData);
    }
	*/
}

void main()
{
    //Initialize screen
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    //1 = ship
    //2 = miss
    int playerGrid[BOARD_LENGTH][BOARD_WIDTH];
    int computerGrid[BOARD_LENGTH][BOARD_WIDTH];
    struct ships compShips;
    struct ships playerShips;

    //location of displays
    int playerBoardX = 5;
    int playerBoardY = 1;
    int cpuBoardX = 35;
    int cpuBoardY = 1;

    //set everything to 0 (for sanity's sake) Might not need this
    for (int i = 0; i < BOARD_LENGTH; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            playerGrid[i][j] = 0;
            computerGrid[i][j] = 0;
        }
    }

    playerGrid[1][10] = 2;
    playerGrid[2][4] = 1;
    playerGrid[9][3] = 1;

	//initial displays 
	displayCurrentBoard(playerGrid, playerBoardX, playerBoardY);
	displayCurrentBoard(computerGrid, cpuBoardX, cpuBoardY);

    //Main loop
    while (1){
        //place user ships

        //place bot ships

        //loop through player and ship picking locations to shoot
            //end conditions
    }

    //Exit screen
    endwin();
}
