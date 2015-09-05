#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>


char box[21][21];
int queue_1[1000];
int queue_2[1000];
int head = -1;
int tail = -1;
int food = 0;
int food_row, food_column;
char food_char = '@';
int score = 0;

int i,j,n=21;//n is row == column means square box

int main(){
    int choose;
    gotoxy(10,10);
    printf("1.Start game");
    gotoxy(10,11);
    printf("2.Exit");
    gotoxy(10,12);
    printf("Press: ");
    scanf("%d", &choose);
    system("cls");
    switch(choose){
    case 1:
        new_game();
        break;
    case 2:
        return 0;
    }
    return 0;
}

void new_game(){
    int row=6,column=1,n=1;
    char direction='d';
    system("COLOR 3");
    border();
    for(i=0; i<=2; i++){
        column++;
        add_queue(row, column);
    }
    snake_food();
    print_all();
    while(1){
        set_background();
        snake_food();

        // input direction form user and set next move
        if( kbhit())// only allow w s a d
        {
            direction = getch();
        }
        if(direction == 'w'){ //up
            row--;
        }
         if(direction == 's'){//down
            row++;
        }
        if(direction == 'a'){//left
            column--;
        }

        if(direction == 'd'){//right
            column++;
        }

        printf("-- %c --", box[row][column]);

        if(is_game_over(row, column)) {
            return 0;
        }

        add_queue(row, column);// Insert new move

        eat_food(row, column);

        set_queue_to_box();// set snake body to box from queue
        print_all(); // display the box
        Sleep(300);
    }
}

int is_game_over(int row, int column) {
    if(box[row][column] == '*')
    {
        game_over();
        return 1;
    }

    // body collition with loop
    for(i=head; i<=tail; i++){
        if(row == queue_1[i] && column == queue_2[i]){
            game_over();
            return 1;
        }
    }

    return 0;
}

void game_over() {
    system("cls");
    gotoxy(10,10);
    printf("Game Over!");
    gotoxy(10,11);
    printf("End game");
    gotoxy(20,20);
}

void eat_food(int row, int column) {
    if(box[row][column] == food_char) { // eat food
        score++;
        food = 0;
    } else {
        pop_queue();// cut one step from snake tail
    }
}

void snake_food(){
    if(food == 0){
        create_food();
        food = 1;
    }
    box[food_row][food_column] = food_char; //print food in box
}


void create_food(){
    //int row_1,column_1;
    food_row = rand() % 19 + 1;
    food_column = rand() % 19 + 1;
    /*if(head == -1){
        head = 0;
    }
    if(tail == -1){
        tail = 0;
    }
    for(i=head; i<=tail; i++){// check snake body
        if(row_1 != queue_1[i] && column_1 != queue_2[i]){
            box[row_1][column_1] = '7';
            food = 1;
        }
        return 0;
    }
    snake_food();*/
    //box[row_1][column_1] = '0';
    //food = 1;
}


void add_queue(int row, int column){
    (tail == -1) ? (tail = 0) : tail++;
    queue_1[tail] = row;
    queue_2[tail] = column;
}

void pop_queue(){
    if(head == -1){
        head = 0;
    }
    else{
        head++;
    }
}

void set_queue_to_box(){
    int row,coloum;
    if(head == -1){
        head = 0;
    }
    for(i=head; i<=tail; i++){
        row = queue_1[i];
        coloum = queue_2[i];
        box[row][coloum] = 'o';
    }
}

void set_background() {
    for(i=1; i<n-1; i++){
        for(j=1; j<n-1; j++){
            box[i][j] = ' ';//fill background with space
        }
    }
}

void border(){
    //Border start here
    for(i=0; i<n; i++){
        box[i][0] = '*'; //left wall
        box[i][n-1] = '*';//right wall
        box[0][i] = '*'; // top wall
        box[n-1][i] = '*';// bottom wall
    }
    //Border finished here
}

void print_all(){
    system("cls");
    printf("score: %d \n", score);
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%c", box[i][j]);
            if(j == n-1){
                printf("\n");
            }
        }
    }
}

void gotoxy (int x, int y){
    COORD coord; // coordinates
    coord.X = x;
    coord.Y = y; // X and Y coordinates

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

