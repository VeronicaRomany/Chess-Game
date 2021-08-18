#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define maxmoves 2000
//functions prototype
void get_input(int turn);
bool check_valid_move(int fromrow,int fromcolumn,int torow,int tocolumn);
bool Check_the_way(int fromrow, int fromcolumn, int torow, int tocolumn);
void Printing_board();
void data(int fromrow,int fromcolumn,int torow,int tocolumn,int turn);
void changed(char eat,int turn);
void checkMate(int fromrow,int fromcolumn,int torow,int tocolumn,int turn);
bool safe_my_king_Black();
bool safe_my_king_white();
// Global variables:
// the board:
char game[10][10]=
{

    {'\0','A','B','C','D','E','F','G','H','\0'},
    {'1','R','N','B','Q','K','B','N','R','1'},
    {'2','P','P','P','P','P','P','P','P','2'},
    {'3','-','.','-','.','-','.','-','.','3'},
    {'4','.','-','.','-','.','-','.','-','4'},
    {'5','-','.','-','.','-','.','-','.','5'},
    {'6','.','-','.','-','.','-','.','-','6'},
    {'7','p','p','p','p','p','p','p','p','7'},
    {'8','r','n','b','q','k','b','n','r','8'},
    {'\0','A','B','C','D','E','F','G','H','\0'},

};

//the index
char fromcolumn;
int fromrow;
char tocolumn;
int torow;
char replace;                             //used in promotion to represent the piece which the pawn is replaced by
int attackerrow;
int attackercolumn ;
char attackerpiece;
int promsuccess ;
//the valid move
bool validmove;
bool takemove;
bool clearpath;
bool checkedposition;
bool checkedway;
bool checkedking;
bool stupidmovewhite;
bool stupidmoveblack;
bool END;
//eaten:
char white_eaten[100];
char black_eaten[100];
char eaten;
int index_white_eaten=0;
int index_black_eaten=0;
//undo
int history [maxmoves][4];
char change[maxmoves][1];
char undoCase ;
int doneRedo;
int promoturn;                                              //an integer refers to the turn when a pawn was promoted

////////////////////////////////////////////////////////FUNCTIONS////////////////////////////////////////////////////////////////////////////////////////////
bool Can_white_piece_move(){
    char tmp1;
    char tmp2;

    for(int i=1 ; i<9 ; i++){
        for(int j=1 ; j<9 ; j++){
            for(int x=1 ; x<9 ; x++){
                for(int y=1 ; y<9 ; y++){
                    if(game[i][j]>='a' && game[i][j]<='z' && check_valid_move(i,j,x,y)==true && Check_the_way(i,j,x,y)==true){
                            tmp1=game[x][y];
                            tmp2=game[i][j];

                            game[x][y]=game[i][j];
                            game[i][j]='-';

                            if(safe_my_king_white()==true){
                                game[x][y]=tmp1;
                                game[i][j]=tmp2;
                                return true;
                            }else{
                                game[x][y]=tmp1;
                                game[i][j]=tmp2;
                            }
                        }
                    }
                }
            }
        }
    return false;
}

bool Can_Black_piece_move(){
    char tmp1;
    char tmp2;

    for(int i=1 ; i<9 ; i++){
        for(int j=1 ; j<9 ; j++){
            for(int x=1 ; x<9 ; x++){
                for(int y=1 ; y<9 ; y++){
                    if(game[i][j]>='A' && game[i][j]<='Z' && check_valid_move(i,j,x,y)==true && Check_the_way(i,j,x,y)==true){
                            tmp1=game[x][y];
                            tmp2=game[i][j];

                            game[x][y]=game[i][j];
                            game[i][j]='-';

                            if(safe_my_king_Black()==true){
                                game[x][y]=tmp1;
                                game[i][j]=tmp2;
                                return true;
                            }else{
                                game[x][y]=tmp1;
                                game[i][j]=tmp2;
                            }
                        }
                    }
                }
            }
        }
    return false;
}


bool Stalemate_black(){             //check is there is a stalemate on the black king(white turn)
                                    // around the king is not valid to move
    bool No_legal_movement;
    int king_row_position;
    int king_column_position;
    int tmp1;
    int tmp2;
    int tmp3;
    int tmp4;
    int tmp5;
    int tmp6;
    int tmp7;
    int tmp8;

// find the black king
    for(int i=1 ; i<9 ; i++){
        for(int j=1 ; j<9 ; j++){
            if(game[i][j]=='K'){
                king_row_position=i;
                king_column_position=j;
                break;
            }
        }
    }

    //special cases
  if(king_row_position==1 && king_column_position==1){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,1,2)==true && Check_the_way(i,j,1,2)==true && (game[1][2]=='-' || game[1][2]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

  for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,2,1)==true && Check_the_way(i,j,2,1)==true &&(game[2][1]=='-' || game[2][1]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,2,2)==true && Check_the_way(i,j,2,2)==true && (game[2][2]=='-' || game[2][2]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

    if(king_row_position==1 && king_column_position==8){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,1,7)==true && Check_the_way(i,j,1,7)==true && (game[1][7]=='-' || game[1][7]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

  for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,2,7)==true && Check_the_way(i,j,2,7)==true && (game[2][7]=='-' || game[2][7]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,2,8)==true && Check_the_way(i,j,2,8)==true && (game[2][8]=='-' || game[2][8]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();


    if(tmp1==1 && tmp2==1 && tmp3==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

  if(king_row_position==8 && king_column_position==1){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,7,1)==true && Check_the_way(i,j,7,1)==true && (game[7][1]=='-' || game[7][1]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

  for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,7,2)==true && Check_the_way(i,j,7,2)==true && (game[7][2]=='-' || game[7][2]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,8,2)==true && Check_the_way(i,j,8,2)==true && (game[8][2]=='-' || game[8][2]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

 if(king_row_position==8 && king_column_position==8){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,8,7)==true && Check_the_way(i,j,8,7)==true && (game[8][7]=='-' || game[8][7]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

  for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,7,7)==true && Check_the_way(i,j,7,7)==true && (game[7][7]=='-' || game[7][7]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,7,8)==true && Check_the_way(i,j,7,8)==true && (game[7][8]=='-' || game[7][8]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }
    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}


    if(king_column_position==8 && king_row_position!=1 && king_row_position!=8 ){

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position-1)==true && Check_the_way(i,j,king_row_position-1,king_column_position-1)==true
                   && (game[king_row_position-1][king_column_position-1]=='-' || game[king_row_position-1][king_column_position-1]=='.' )){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position)==true && Check_the_way(i,j,king_row_position-1,king_column_position)==true &&
                   (game[king_row_position-1][king_column_position]=='-' || game[king_row_position-1][king_column_position]=='.' )){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position,king_column_position-1)==true && Check_the_way(i,j,king_row_position,king_column_position-1)==true &&
                   (game[king_row_position][king_column_position-1]=='-' || game[king_row_position][king_column_position-1]=='.' )){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position-1)==true && Check_the_way(i,j,king_row_position+1,king_column_position-1)==true &&
                   (game[king_row_position+1][king_column_position-1]=='-' || game[king_row_position+1][king_column_position-1]=='.' )){
                    tmp4=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position)==true && Check_the_way(i,j,king_row_position+1,king_column_position)==true &&
                   (game[king_row_position+1][king_column_position]=='-' || game[king_row_position+1][king_column_position]=='.' )){
                    tmp5=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1&& No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

     if(king_column_position==1 && king_row_position!=1 && king_row_position!=8 ){

        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]>='a' && game[i][j]<='z'){
                    if(check_valid_move(i,j,king_row_position-1,king_column_position)==true && Check_the_way(i,j,king_row_position-1,king_column_position)==true &&
                    (game[king_row_position-1][king_column_position]=='-' || game[king_row_position-1][king_column_position]=='.' )){
                        tmp1=1;
                        i=10;
                        j=10;
                    }
                }
            }
        }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position)==true && Check_the_way(i,j,king_row_position+1,king_column_position)==true &&
                   (game[king_row_position+1][king_column_position]=='-' || game[king_row_position+1][king_column_position]=='.' )){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position+1)==true && Check_the_way(i,j,king_row_position-1,king_column_position+1)==true &&
                   (game[king_row_position-1][king_column_position+1]=='-' || game[king_row_position-1][king_column_position+1]=='.' )){
                    tmp3=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position,king_column_position+1)==true && Check_the_way(i,j,king_row_position,king_column_position+1)==true &&
                   (game[king_row_position][king_column_position+1]=='-' || game[king_row_position][king_column_position+1]=='.' )){
                    tmp4=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position+1)==true && Check_the_way(i,j,king_row_position+1,king_column_position+1)==true &&
                   (game[king_row_position+1][king_column_position+1]=='-' || game[king_row_position+1][king_column_position+1]=='.' )){
                    tmp5=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1&& No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

     if(king_row_position==8 && king_column_position!=1 && king_column_position!=8 ){

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position-1)==true && Check_the_way(i,j,king_row_position-1,king_column_position-1)==true &&
                   (game[king_row_position-1][king_column_position-1]=='-' || game[king_row_position-1][king_column_position-1]=='.' )){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position)==true && Check_the_way(i,j,king_row_position-1,king_column_position)==true &&
                   (game[king_row_position-1][king_column_position]=='-' || game[king_row_position-1][king_column_position]=='.' )){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position+1)==true && Check_the_way(i,j,king_row_position-1,king_column_position+1)==true &&
                   (game[king_row_position-1][king_column_position+1]=='-' || game[king_row_position-1][king_column_position+1]=='.' )){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position,king_column_position+1)==true && Check_the_way(i,j,king_row_position,king_column_position+1)==true &&
                   (game[king_row_position][king_column_position+1]=='-' || game[king_row_position][king_column_position+1]=='.' )){
                    tmp4=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position,king_column_position-1)==true && Check_the_way(i,j,king_row_position,king_column_position-1)==true &&
                   (game[king_row_position][king_column_position-1]=='-' || game[king_row_position][king_column_position-1]=='.' )){
                    tmp5=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}


     if(king_row_position==1 && king_column_position!=1 && king_column_position!=8 ){

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position,king_column_position-1)==true && Check_the_way(i,j,king_row_position,king_column_position-1)==true &&
                   (game[king_row_position][king_column_position-1]=='-' || game[king_row_position][king_column_position-1]=='.' )){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position,king_column_position+1)==true && Check_the_way(i,j,king_row_position,king_column_position+1)==true &&
                   (game[king_row_position][king_column_position+1]=='-' || game[king_row_position][king_column_position+1]=='.' )){
                    tmp2=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position+1)==true && Check_the_way(i,j,king_row_position+1,king_column_position+1)==true &&
                   (game[king_row_position+1][king_column_position+1]=='-' || game[king_row_position+1][king_column_position+1]=='.' )){
                    tmp3=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position-1)==true && Check_the_way(i,j,king_row_position+1,king_column_position-1)==true &&
                   (game[king_row_position+1][king_column_position-1]=='-' || game[king_row_position+1][king_column_position-1]=='.' )){
                    tmp4=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position)==true && Check_the_way(i,j,king_row_position+1,king_column_position)==true &&
                   (game[king_row_position+1][king_column_position]=='-' || game[king_row_position+1][king_column_position]=='.' )){
                    tmp5=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1&& No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

    //general position

if(king_row_position!=1 && king_row_position!=8 && king_column_position!=1 && king_column_position!=8){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position-1)==true && Check_the_way(i,j,king_row_position-1,king_column_position-1)==true &&
                   (game[king_row_position-1][king_column_position-1]=='-' || game[king_row_position-1][king_column_position-1]=='.' )){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position)==true && Check_the_way(i,j,king_row_position-1,king_column_position)==true &&
                   (game[king_row_position-1][king_column_position]=='-' || game[king_row_position-1][king_column_position]=='.' )){
                    tmp2=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position+1)==true && Check_the_way(i,j,king_row_position-1,king_column_position+1)==true &&
                   (game[king_row_position-1][king_column_position+1]=='-' || game[king_row_position-1][king_column_position+1]=='.' )){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position,king_column_position-1)==true && Check_the_way(i,j,king_row_position,king_column_position-1)==true &&
                   (game[king_row_position][king_column_position-1]=='-' || game[king_row_position][king_column_position-1]=='.' )){
                    tmp4=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position,king_column_position+1)==true && Check_the_way(i,j,king_row_position,king_column_position+1)==true &&
                   (game[king_row_position][king_column_position+1]=='-' || game[king_row_position][king_column_position+1]=='.' )){
                    tmp5=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position-1)==true && Check_the_way(i,j,king_row_position+1,king_column_position-1)==true &&
                   (game[king_row_position+1][king_column_position-1]=='-' || game[king_row_position+1][king_column_position-1]=='.' )){
                    tmp6=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position)==true && Check_the_way(i,j,king_row_position+1,king_column_position)==true &&
                   (game[king_row_position+1][king_column_position]=='-' || game[king_row_position+1][king_column_position]=='.' )){
                    tmp7=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position+1)==true && Check_the_way(i,j,king_row_position+1,king_column_position+1)==true &&
                   (game[king_row_position+1][king_column_position+1]=='-' || game[king_row_position+1][king_column_position+1]=='.' )){
                    tmp8=1;
                    i=10;
                    j=10;
                }
            }
        }
    }
    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1 && tmp6==1 && tmp7==1 && tmp8==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}
}

bool Stalemate_white(){             //check is there is a stalemate on the white king(black turn)
                                    //around the white king is valid
    int king_row_position;
    int king_column_position;
    int tmp1;
    int tmp2;
    int tmp3;
    int tmp4;
    int tmp5;
    int tmp6;
    int tmp7;
    int tmp8;
    bool No_legal_movement;
// find the white king
    for(int i=1 ; i<9 ; i++){
        for(int j=1 ; j<9 ; j++){
            if(game[i][j]=='k'){
                king_row_position=i;
                king_column_position=j;
                break;
            }
        }
    }

    //special cases
  if(king_row_position==1 && king_column_position==1){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,1,2)==true && Check_the_way(i,j,1,2)==true && (game[1][2]=='-' || game[1][2]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

  for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,2,1)==true && Check_the_way(i,j,2,1)==true && (game[2][1]=='-' || game[2][1]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,2,2)==true && Check_the_way(i,j,2,2)==true && (game[2][2]=='-' || game[2][2]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_white_piece_move();
    if(tmp1==1 && tmp2==1 && tmp3==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

    if(king_row_position==1 && king_column_position==8){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,1,7)==true && Check_the_way(i,j,1,7)==true && (game[1][7]=='-' || game[1][7]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

  for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,2,7)==true && Check_the_way(i,j,2,7)==true && (game[2][7]=='-' || game[2][7]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,2,8)==true && Check_the_way(i,j,2,8)==true && (game[2][8]=='-' || game[2][8]=='.')){
                    tmp3=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1&& No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

  if(king_row_position==8 && king_column_position==1){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,7,1)==true && Check_the_way(i,j,7,1)==true && (game[7][1]=='-' || game[7][1]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

  for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,7,2)==true && Check_the_way(i,j,7,2)==true && (game[7][2]=='-' || game[7][2]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,8,2)==true && Check_the_way(i,j,8,2)==true && (game[8][2]=='-' || game[8][2]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }
    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

 if(king_row_position==8 && king_column_position==8){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,8,7)==true && Check_the_way(i,j,8,7)==true && (game[8][7]=='-' || game[8][7]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

  for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,7,7)==true && Check_the_way(i,j,7,7)==true && (game[7][7]=='-' || game[7][7]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,7,8)==true && Check_the_way(i,j,7,8)==true && (game[7][8]=='-' || game[7][8]=='.')){
                    tmp3=1;
                   i=10;
                    j=10;
                }
            }
        }
    }
    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }

  }


    if(king_column_position==8 && king_row_position!=1 && king_row_position!=8 ){

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position-1)==true && Check_the_way(i,j,king_row_position-1,king_column_position-1)==true &&
                   (game[king_row_position-1][king_column_position-1]=='-' || game[king_row_position-1][king_column_position-1]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position)==true && Check_the_way(i,j,king_row_position-1,king_column_position)==true &&
                    (game[king_row_position-1][king_column_position]=='-' || game[king_row_position-1][king_column_position]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position,king_column_position-1)==true && Check_the_way(i,j,king_row_position,king_column_position-1)==true &&
                    (game[king_row_position][king_column_position-1]=='-' || game[king_row_position][king_column_position-1]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position-1)==true && Check_the_way(i,j,king_row_position+1,king_column_position-1)==true &&
                    (game[king_row_position+1][king_column_position-1]=='-' || game[king_row_position+1][king_column_position-1]=='.')){
                    tmp4=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position)==true && Check_the_way(i,j,king_row_position+1,king_column_position)==true &&
                    (game[king_row_position+1][king_column_position]=='-' || game[king_row_position+1][king_column_position]=='.')){
                    tmp5=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

     if(king_column_position==1 && king_row_position!=1 && king_row_position!=8 ){

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position)==true && Check_the_way(i,j,king_row_position-1,king_column_position)==true &&
                    (game[king_row_position-1][king_column_position]=='-' || game[king_row_position-1][king_column_position]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position)==true && Check_the_way(i,j,king_row_position+1,king_column_position)==true &&
                    (game[king_row_position+1][king_column_position]=='-' || game[king_row_position+1][king_column_position]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position+1)==true && Check_the_way(i,j,king_row_position-1,king_column_position+1)==true &&
                    (game[king_row_position-1][king_column_position+1]=='-' || game[king_row_position-1][king_column_position+1]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position,king_column_position+1)==true && Check_the_way(i,j,king_row_position,king_column_position+1)==true &&
                    (game[king_row_position][king_column_position+1]=='-' || game[king_row_position][king_column_position+1]=='.')){
                    tmp4=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position+1)==true && Check_the_way(i,j,king_row_position+1,king_column_position+1)==true &&
                    (game[king_row_position+1][king_column_position+1]=='-' || game[king_row_position+1][king_column_position+1]=='.')){
                    tmp5=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}


     if(king_row_position==8 && king_column_position!=1 && king_column_position!=8 ){

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position-1)==true && Check_the_way(i,j,king_row_position-1,king_column_position-1)==true &&
                    (game[king_row_position-1][king_column_position-1]=='-' || game[king_row_position-1][king_column_position-1]=='.')){
                    tmp1=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position)==true && Check_the_way(i,j,king_row_position-1,king_column_position)==true &&
                    (game[king_row_position-1][king_column_position]=='-' || game[king_row_position-1][king_column_position]=='.')){
                    tmp2=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position+1)==true && Check_the_way(i,j,king_row_position-1,king_column_position+1)==true &&
                    (game[king_row_position-1][king_column_position+1]=='-' || game[king_row_position-1][king_column_position+1]=='.')){
                    tmp3=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position,king_column_position+1)==true && Check_the_way(i,j,king_row_position,king_column_position+1)==true &&
                    (game[king_row_position][king_column_position+1]=='-' || game[king_row_position][king_column_position+1]=='.')){
                    tmp4=1;
                  i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position,king_column_position-1)==true && Check_the_way(i,j,king_row_position,king_column_position-1)==true &&
                    (game[king_row_position][king_column_position-1]=='-' || game[king_row_position][king_column_position-1]=='.')){
                    tmp5=1;
                    i=10;
                    j=10;
                }
            }
        }
    }
    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}


     if(king_row_position==1 && king_column_position!=1 && king_column_position!=8 ){

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position,king_column_position-1)==true && Check_the_way(i,j,king_row_position,king_column_position-1)==true &&
                    (game[king_row_position][king_column_position-1]=='-' || game[king_row_position][king_column_position-1]=='.')){
                    tmp1=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position,king_column_position+1)==true && Check_the_way(i,j,king_row_position,king_column_position+1)==true &&
                    (game[king_row_position][king_column_position+1]=='-' || game[king_row_position][king_column_position+1]=='.')){
                    tmp2=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position+1)==true && Check_the_way(i,j,king_row_position+1,king_column_position+1)==true &&
                    (game[king_row_position+1][king_column_position+1]=='-' || game[king_row_position+1][king_column_position+1]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position-1)==true && Check_the_way(i,j,king_row_position+1,king_column_position-1)==true &&
                    (game[king_row_position+1][king_column_position-1]=='-' || game[king_row_position+1][king_column_position-1]=='.')){
                    tmp4=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position)==true && Check_the_way(i,j,king_row_position+1,king_column_position)==true &&
                    (game[king_row_position+1][king_column_position]=='-' || game[king_row_position+1][king_column_position]=='.')){
                    tmp5=1;
                    i=10;
                    j=10;
                }
            }
        }
    }
    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1 && No_legal_movement==false){
        return true;
    }else{
        return false;
    }
}

//general position

if(king_row_position!=1 && king_row_position!=8 && king_column_position!=1 && king_column_position!=8){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position-1)==true && Check_the_way(i,j,king_row_position-1,king_column_position-1)==true&&
                    (game[king_row_position-1][king_column_position-1]=='-' || game[king_row_position-1][king_column_position-1]=='.')){
                    tmp1=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position)==true && Check_the_way(i,j,king_row_position-1,king_column_position)==true&&
                    (game[king_row_position-1][king_column_position]=='-' || game[king_row_position-1][king_column_position]=='.')){
                    tmp2=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position-1,king_column_position+1)==true && Check_the_way(i,j,king_row_position-1,king_column_position+1)==true&&
                    (game[king_row_position-1][king_column_position+1]=='-' || game[king_row_position-1][king_column_position+1]=='.')){
                    tmp3=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position,king_column_position-1)==true && Check_the_way(i,j,king_row_position,king_column_position-1)==true&&
                    (game[king_row_position][king_column_position-1]=='-' || game[king_row_position][king_column_position-1]=='.')){
                    tmp4=1;
                   i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position,king_column_position+1)==true && Check_the_way(i,j,king_row_position,king_column_position+1)==true &&
                    (game[king_row_position][king_column_position+1]=='-' || game[king_row_position][king_column_position+1]=='.')){
                    tmp5=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position-1)==true && Check_the_way(i,j,king_row_position+1,king_column_position-1)==true&&
                    (game[king_row_position+1][king_column_position-1]=='-' || game[king_row_position+1][king_column_position-1]=='.')){
                    tmp6=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position)==true && Check_the_way(i,j,king_row_position+1,king_column_position)==true &&
                    (game[king_row_position+1][king_column_position]=='-' || game[king_row_position+1][king_column_position]=='.')){
                    tmp7=1;
                    i=10;
                    j=10;
                }
            }
        }
    }

     for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,king_row_position+1,king_column_position+1)==true && Check_the_way(i,j,king_row_position+1,king_column_position+1)==true&&
                    (game[king_row_position+1][king_column_position+1]=='-' || game[king_row_position+1][king_column_position+1]=='.')){
                    tmp8=1;
                    i=10;
                    j=10;
                }
            }
        }
    }
    No_legal_movement=Can_Black_piece_move();

    if(tmp1==1 && tmp2==1 && tmp3==1 && tmp4==1 && tmp5==1 && tmp6==1 && tmp7==1 && tmp8==1&& No_legal_movement==false){

        return true;
    }else{
        return false;
    }
}
}

bool Draw(){
    int Number_of_pieces=0;
    char piece1;
    char piece2;
    int row1;
    int col1;
    int row2;
    int col2;
//find number of pieces on the board
    for(int i=1; i<9 ; i++){
        for(int j=1 ; j<9 ; j++){
            if(game[i][j]!='K' && game[i][j]!='k' && game[i][j]!='-' && game[i][j]!='.'){
                Number_of_pieces+=1;
            }
        }
    }

    if(Number_of_pieces>2){
        return false;
    }

    if(Number_of_pieces==0){
        return true;
    }

    if(Number_of_pieces==1){
        for(int i=1; i<9 ; i++){
            for(int j=1 ; j<9 ; j++){
                if(game[i][j]!='K' && game[i][j]!='k' && game[i][j]!='-' && game[i][j]!='.'){
                    if(game[i][j]=='b' || game[i][j]=='B' || game[i][j]=='n' || game[i][j]=='N'){
                        return true;
                    }else{
                        return false;
                    }
                }
            }
        }
    }

    if(Number_of_pieces==2){
        for(int i=1; i<9 ; i++){
            for(int j=1 ; j<9 ; j++){
                if(game[i][j]!='K' && game[i][j]!='k' && game[i][j]!='-' && game[i][j]!='.'){
                       piece1=game[i][j];
                       row1=i;
                       col1=j;
                       game[i][j]='.';
                       i=10;
                       j=10;
                }
            }
        }
        for(int i=1; i<9 ; i++){
            for(int j=1 ; j<9 ; j++){
                if(game[i][j]!='K' && game[i][j]!='k' && game[i][j]!='-' && game[i][j]!='.' ){
                       piece2=game[i][j];
                       row2=i;
                       col2=j;
                       i=10;
                       j=10;
                }
            }
        }
        if((piece1=='n'&&piece2=='n')||(piece1=='N'&&piece2=='N')){
            return true;
        }else{
            game[row1][col1]=piece1;
            game[row2][col2]=piece2;
        }
    }
    return false;
}

void Save_my_game(int turn){
    char filename[200];
            FILE * fileopen;
    do{
        printf("Enter file name: ");                //ask the user for the file name
        gets(filename);
        fileopen= fopen(filename,"w");                    // r for read from the file
            if(fileopen==NULL){
                printf("File not found,try again\n");
            }
        }
        while(fileopen==NULL);

    // save the last board
    for(int x=0 ; x<10 ; x++){
        for(int y=0 ; y<10 ; y++){
            fputc(game[x][y], fileopen);
            fputc('\n',fileopen);
        }
    }
    // save black eaten pieces
    for(int i=0 ; i<index_black_eaten ; i++){
        fputc(black_eaten[i],fileopen);
        fputc('\n',fileopen);
    }

    fputc('$',fileopen);
    fputc('\n',fileopen);
    // save white eaten pieces
    for(int j=0 ;  j<index_white_eaten ; j++){
        fputc(white_eaten[j],fileopen);
        fputc('\n',fileopen);
    }

    // save the turn
    fputc('$',fileopen);
    fputc('\n',fileopen);
    fprintf(fileopen, "%d", turn);
    fputc('\n',fileopen);

    for(int i=0 ; i<turn-1 ; i++){
        for(int j=0 ; j<4 ; j++){
            fprintf(fileopen, "%d", history[i][j]);
            fputc('\n',fileopen);
        }
    }

    for(int n=0 ;  n<turn ; n++){
        fputc(change[n][0],fileopen);
        fputc('\n',fileopen);
    }
    //close the file
    fclose(fileopen);

    printf("Your game saved successfully, See you later :) \n");             // success message
}

int Load_game(){
    int turn;
    char filename[200];
        FILE * filesaved;
    do{
        printf("Enter file name: ");                //ask the user for the file name
        gets(filename);
        filesaved= fopen(filename,"r");                    // r for read from the file
            if(filesaved==NULL){
                printf("File not found, try again\n");
            }
        }
        while(filesaved==NULL);

    for(int x=0 ; x<10 ; x++){                  // save the last board
        for(int y=0 ; y<10 ; y++){
            game[x][y]=getc(filesaved);
            getc(filesaved);
        }
    }

    char loadeaten=getc(filesaved);
    getc(filesaved);

    while (loadeaten!='$'){
        black_eaten[index_black_eaten++]=loadeaten;
        loadeaten=getc(filesaved);
        getc(filesaved);
    }

    loadeaten=getc(filesaved);
    getc(filesaved);

    while(loadeaten !='$'){
        white_eaten[index_white_eaten++]=loadeaten;
        loadeaten=getc(filesaved);
        getc(filesaved);
    }

    fscanf(filesaved, "%d", &turn);
    getc(filesaved);

    for(int i=0 ; i<turn-1 ; i++){                  // save the last board
        for(int y=0 ; y<4 ; y++){
            fscanf(filesaved, "%d", &history[i][y]);
            getc(filesaved);
        }
    }

     for(int n=0 ; n<turn ; n++){
        change[n][0]=getc(filesaved);
        getc(filesaved);
    }

    fclose(filesaved);
    return turn;
}

bool check(int turn){
    int x,y;                             //king index
    if(turn%2!=0){                      //white check black
        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]=='K'){  //find the position of the black king in theboard //
                    x=i;
                    y=j;
                    break;
                }
            }
        }

        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]>='a'&&game[i][j]<='z'){
                    checkedposition = check_valid_move(i,j,x,y);
                    checkedway = Check_the_way(i,j,x,y);

                    if(checkedposition==true && checkedway==true){
                        attackerrow=i;
                        attackercolumn=j;
                        attackerpiece=game[attackerrow][attackercolumn];

                        printf("Black King is under check\n");
                        checkMate(fromrow,fromcolumn,torow,tocolumn,turn);
                        return true;
                        break;
                    }
                }
            }
            if(i==8){
                return false;
            }
        }
    }

    if(turn%2==0){
        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]=='k'){       //find the position of the white king in the board //
                    x=i;
                    y=j;
                    break;
                }
            }
        }
        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]>='A'&&game[i][j]<='Z'){
                    checkedposition = check_valid_move(i,j,x,y);
                    checkedway = Check_the_way(i,j,x,y);

                    if(checkedposition==true && checkedway==true){
                        attackerrow=i;
                        attackercolumn=j;
                        attackerpiece=game[attackerrow][attackercolumn];

                        printf("White King is under check\n");
                        checkMate(fromrow,fromcolumn,torow,tocolumn,turn);
                        return true;
                        break;
                    }
                }
            }
            if(i==8){
                return false;

            }
        }
    }
}
bool Recheck(int turn){
    int x,y;                            //king index
    if(turn%2!=0){                      //white check black
        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]=='K'){  //find the position of the black king in the board //
                    x=i;
                    y=j;
                    break;
                }
            }
        }

        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]>='a'&&game[i][j]<='z'){
                    checkedposition = check_valid_move(i,j,x,y);
                    checkedway = Check_the_way(i,j,x,y);

                    if(checkedposition==true && checkedway==true){
                        checkedking=true;
                        return true;
                        break;
                    }
                }
            }
            if(i==8){
                return false;
            }
        }
    }

    if(turn%2==0){
        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]=='k'){    //find the position of the white king in the board //
                    x=i;
                    y=j;
                    break;
                }
            }
        }


        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]>='A'&&game[i][j]<='Z'){
                    checkedposition = check_valid_move(i,j,x,y);
                    checkedway = Check_the_way(i,j,x,y);

                    if(checkedposition==true && checkedway==true){
                            attackerrow=i;
                            attackercolumn=j;
                            attackerpiece=game[attackerrow][attackercolumn];
                            checkedking=true;
                            return true;
                            break;
                        }
                    }
                }
            if(i==8){
                return false;
            }
        }
    }
}

// check the first move
bool isfirst(int fromrow,int fromcolumn){
    if(game[fromrow][fromcolumn]=='P'){          //check if the black pawn is moving for the first time
        if(fromrow == 2){
            return true;
        }else{
            return false;
        }
    }

    if(game[fromrow][fromcolumn]=='p'){         //check if the white pawn is moving for the first time
        if(fromrow == 7){
            return true;
        }else{
            return false;
        }
    }
}

//promotion
bool promotion(int fromrow,int fromcolumn,int torow, int tocolumn,int turn){
    if(turn%2==0){                      //black pawn //
        if ((game[fromrow][fromcolumn]=='P')&&(fromrow==7) && (torow==8)){
            printf("\nyou pawn can be promoted :PLEASE ENTER ONE PIECE FROM (Q-N-R-B): \n");
            scanf("%c",&replace);
            while(getchar()!='\n');

            if(replace=='Q'|| replace=='N'|| replace=='B'||replace=='R'){
                     undoCase = game[8][tocolumn];        //this char is used in case of the player wants to undo the promotion
                game[8][tocolumn]=replace;
                if(fromcolumn%2==0){
                    game[7][fromcolumn]='.';
                }else{
                    game[7][fromcolumn]='-';
                }
                promoturn=turn;
                Printing_board();
                char x='P';
                changed(x,turn);
            }else{
                printf("\n Warning: PLEASE ENTER ONE PIECE FROM (Q-N-R-B): \n");    // if the player entered a piece from the white team or unknown piece//
                promotion(fromrow,fromcolumn,torow,tocolumn,turn);
            }
            promsuccess=1;

            data(fromrow,fromcolumn,torow,tocolumn,turn);

            return true ;
        }else{
            return false ;
        }
    }

    if(turn%2!=0){                                 //white pawn //
        if((game[fromrow][fromcolumn]=='p')&&(torow==1 )&& (fromrow==2)){
            printf("\nyour pawn can be promoted : PLEASE ENTER ONE PIECE FROM (q-n-b-r):\n ");
            scanf("%c",&replace);
            while(getchar()!='\n');

            if(replace=='q'|| replace=='n'|| replace=='b'||replace=='r'){
                     undoCase = game[1][tocolumn];        //this char is used in case of the player wants to undo the promotion
                game[1][tocolumn]=replace ;
                if(fromcolumn%2==0){
                    game[2][fromcolumn]='-';
                }else{
                    game[2][fromcolumn]='.';
                }
                 promoturn=turn;
                Printing_board();
                char x='p' ;
                changed(x,turn);
            }else{
                printf("\n Warning: PLEASE ENTER ONE PIECE FROM (q-n-b-r): \n"); //if the player entered a piece from the black team or unknown piece //
                promotion(fromrow,fromcolumn,torow,tocolumn,turn);
            }
            data(fromrow,fromcolumn,torow,tocolumn,turn);
             promsuccess=1;


            return true ;
        }else{
            return false ;
        }
    }
}

// check a valid path for a pawn;
bool Check_pawn_way(int fromrow, int fromcolumn, int torow, int tocolumn){
    if((fromcolumn != tocolumn)||(fromcolumn==tocolumn &&abs(torow-fromrow)==1)){
        return true;
    }

    if(torow-fromrow==2){
        if(game[fromrow+1][fromcolumn]=='-'||game[fromrow+1][fromcolumn]=='.'){
            return true;
        }else{
            return false;
        }
    }

    if(fromrow-torow==2){
        if(game[fromrow-1][fromcolumn]=='-'||game[fromrow-1][fromcolumn]=='.'){
            return true;
        }else{
            return false;
        }
    }
}

// check a valid path for a rook
bool Check_rook_way(int fromrow,int fromcolumn,int torow,int tocolumn){
    if(fromrow==torow){
        if(tocolumn>fromcolumn){
            for(int i=fromcolumn+1 ; i<tocolumn ; i++){
                if(game[fromrow][i]!='-'&&game[fromrow][i]!='.'){
                    return false;
                    break;
                }
                if(i==tocolumn-1){
                    return true ;
                }
            }
        }

        if(tocolumn<fromcolumn){
            for(int i=fromcolumn-1 ; i>tocolumn ; i--){
                if(game[fromrow][i]!='-'&&game[fromrow][i]!='.'){
                    return false;
                    break;
                }
                if(i==tocolumn+1){
                    return true ;
                }
            }
        }
    }

    if(fromcolumn==tocolumn){
        if(torow>fromrow){
            for(int i=fromrow+1 ; i<torow ; i++){
                if(game[i][fromcolumn]!='-'&&game[i][fromcolumn]!='.'){
                    return false;
                    break;
                }
                if(i==torow-1){
                    return true ;
                }
            }
        }

        if(torow<fromrow){
            for(int i=fromrow-1 ; i>torow ; i--){
                if(game[i][fromcolumn]!='-'&&game[i][fromcolumn]!='.'){
                    return false;
                    break;
                }
                if(i==torow+1){
                    return true ;
                }
            }
        }
    }
}

// check a valid path for a bishop
bool Check_bishop_way(int fromrow,int fromcolumn,int torow,int tocolumn){
    int steps;

    if(fromrow>torow && fromcolumn<tocolumn){
        steps=fromrow-torow;

        for(int i=1; i<steps ; i++){
            if(game[fromrow-i][fromcolumn+i]!='-'&&game[fromrow-i][fromcolumn+i]!='.'){
                return false;
                break;
            }
            if(i==steps-1){
                return true;
            }
        }
    }

    if(fromrow<torow && fromcolumn<tocolumn){
        steps=torow-fromrow;

        for(int i=1 ; i<steps ; i++){
            if(game[fromrow+i][fromcolumn+i]!='-'&&game[fromrow+i][fromcolumn+i]!='.'){
                return false;
                break;
            }
            if(i==steps-1)
            {
                return true;
            }
        }
    }

    if(fromrow<torow && fromcolumn>tocolumn){
        steps=torow-fromrow;

        for(int i=1 ; i<steps ; i++){
            if(game[fromrow+i][fromcolumn-i]!='-'&&game[fromrow+i][fromcolumn-i]!='.'){
                return false;
                break;
            }
            if(i==steps-1){
                return true;
            }
        }
    }

    if(fromrow>torow && fromcolumn>tocolumn){
        steps=fromrow-torow;

        for(int i=1; i<steps ; i++){
            if(game[fromrow-i][fromcolumn-i]!='-'&&game[fromrow-i][fromcolumn-i]!='.'){
                return false;
                break;
            }
            if(i==steps-1){
                return true;
            }
        }
    }
}

// check a valid path for a queen
bool Check_queen_way(int fromrow,int fromcolumn,int torow,int tocolumn){
    int steps;

    if((fromrow==torow) &&(fromcolumn!=tocolumn)){
        if(tocolumn>fromcolumn){
            for(int i=fromcolumn+1 ; i<tocolumn ; i++){
                if(game[fromrow][i]!='-'&&game[fromrow][i]!='.'){
                    return false;
                    break;
                }
                if(i==tocolumn-1){
                    return true ;
                    break;
                }
            }
        }

        if(tocolumn<fromcolumn){
            for(int i=fromcolumn-1 ; i>tocolumn ; i--){
                if(game[fromrow][i]!='-'&&game[fromrow][i]!='.'){
                    return false;
                    break;
                }
                if(i==tocolumn+1){
                    return true ;
                    break;
                }
            }
        }
    }

    if((fromcolumn==tocolumn) &&(fromrow!=torow)){
        if(torow>fromrow){
            for(int i=fromrow+1 ; i<torow ; i++){
                if(game[i][fromcolumn]!='-'&&game[i][fromcolumn]!='.'){
                    return false;
                    break;
                }
                if(i==torow-1){
                    return true ;
                    break;
                }
            }
        }

        if(torow<fromrow){
            for(int i=fromrow-1 ; i>torow ; i--){
                if(game[i][fromcolumn]!='-'&&game[i][fromcolumn]!='.'){
                    return false;
                    break;
                }
                if(i==torow+1){
                    return true ;
                    break;
                }
            }
        }
    }

    if(fromrow>torow && fromcolumn<tocolumn){
        steps=fromrow-torow;

        for(int i=1; i<steps ; i++){
            if(game[fromrow-i][fromcolumn+i]!='-'&&game[fromrow-i][fromcolumn+i]!='.'){
                return false;
                break;
            }
            if(i==steps-1){
                return true;
                break;
            }
        }
    }

    if(fromrow<torow && fromcolumn<tocolumn){
        steps=torow-fromrow;

        for(int i=1 ; i<steps ; i++){
            if(game[fromrow+i][fromcolumn+i]!='-' && game[fromrow+i][fromcolumn+i]!='.'){
                return false;
                break;
            }
            if(i==steps-1){
                return true;
                break;
            }
        }
    }

    if(fromrow<torow && fromcolumn>tocolumn){
        steps=torow-fromrow;

        for(int i=1 ; i<steps ; i++){
            if(game[fromrow+i][fromcolumn-i]!='-'&&game[fromrow+i][fromcolumn-i]!='.'){
                return false;
                break;
            }
            if(i==steps-1){
                return true;
                break;
            }
        }
    }

    if(fromrow>torow && fromcolumn>tocolumn){
        steps=fromrow-torow;

        for(int i=1; i<steps ; i++){
            if(game[fromrow-i][fromcolumn-i]!='-'&&game[fromrow-i][fromcolumn-i]!='.'){
                return false;
                break;
            }
            if(i==steps-1){
                return true;
                break;
            }
        }
    }
}

// function to check the way
bool Check_the_way(int fromrow, int fromcolumn, int torow, int tocolumn ){
    bool empty;     //boolean variable for the return
// king 's path always valid & knight's way
    if(game[fromrow][fromcolumn]=='K' ||game[fromrow][fromcolumn]=='k'||game[fromrow][fromcolumn]=='n'||game[fromrow][fromcolumn]=='N'){
        return true;
    }
// Pawn's Way
    if((game[fromrow][fromcolumn]=='P')||(game[fromrow][fromcolumn]=='P')){
        empty=Check_pawn_way(fromrow,fromcolumn,torow,tocolumn);
        return empty;
    }
// Rook's Way
    if(game[fromrow][fromcolumn]=='r'||game[fromrow][fromcolumn]=='R'){
        empty=Check_rook_way(fromrow,fromcolumn,torow,tocolumn);
        return empty;
    }
// Bishop's way
    if(game[fromrow][fromcolumn]=='B'||game[fromrow][fromcolumn]=='b'){
        empty=Check_bishop_way(fromrow,fromcolumn,torow,tocolumn);
        return empty;
    }
// Queen's way
    if(game[fromrow][fromcolumn]=='Q'||game[fromrow][fromcolumn]=='q'){
        empty=Check_queen_way(fromrow,fromcolumn,torow,tocolumn);
        return empty;
    }
}

// the validity of the black pawn
bool black_pawn(int fromrow,int fromcolumn, int torow, int tocolumn){
// move
// is first function that knows is it the first time to move or not
    if(game[torow][tocolumn]=='-' || game[torow][tocolumn]=='.'){
        if(fromcolumn==tocolumn && torow==fromrow+1){
            return true;
        }else{
            if(fromcolumn==tocolumn && torow==fromrow+2 && isfirst(fromrow,fromcolumn)==true){
                return true;
            }else{
                return false;
            }
        }
    }
// eat

    if((game[torow][tocolumn]!='-')&&(game[torow][tocolumn]!='.')){
        if((torow==fromrow+1)&&((tocolumn==fromcolumn+1)||(tocolumn==fromcolumn-1))){
            return true;
        }else{
            return false;
        }
    }
}

// the validity of the white pawn
bool white_pawn (int fromrow,int fromcolumn, int torow, int tocolumn){
//move
// is first function that knows is it the first time to move or not
    if(game[torow][tocolumn]=='-' || game[torow][tocolumn]=='.'){
        if(fromcolumn==tocolumn && torow==fromrow-2 && isfirst(fromrow,fromcolumn)==true){
            return true;
        }else{
            if(fromcolumn==tocolumn && torow==fromrow-1){
                return true;
            }else{
                return false;
            }
        }
    }
//eat
    if((game[torow][tocolumn]!='-')&&(game[torow][tocolumn]!='.')){
        if((torow==fromrow-1)&&((tocolumn==fromcolumn+1)||(tocolumn==fromcolumn-1))){
            return true;
        }else{
            return false;
        }
    }
}

//the validity of the rook
bool Rook(int fromrow,int fromcolumn,int torow, int tocolumn){
    if(((fromrow==torow) &&(fromcolumn!=tocolumn)) || ((fromcolumn==tocolumn)&&(fromrow!=torow))){
        return true;
    }
    else{
        return false;
    }
}

// the validity of the bishop
bool Bishop(int fromrow,int fromcolumn,int torow, int tocolumn){
    if(abs(fromrow-torow)==abs(fromcolumn-tocolumn)){
        return true;
    }else{
        return false;
    }
}

// the validity of the knight
bool knight(int fromrow,int fromcolumn,int torow, int tocolumn){
    if((abs(tocolumn-fromcolumn)==1 && abs(torow-fromrow)==2)||(abs(torow-fromrow)==1 && abs(tocolumn-fromcolumn)==2)){
        return true;
    }else{
        return false;
    }
}

// the validity of the queen
bool Queen(int fromrow, int fromcolumn, int torow, int tocolumn){
    if((abs(fromrow-torow)==abs(fromcolumn-tocolumn))|| ((fromrow==torow) &&(fromcolumn!=tocolumn)) || ((fromcolumn==tocolumn)&&(fromrow!=torow))){
        return true;
    }else{
        return false;
    }
}

// the validity of king
bool King(int fromrow,int fromcolumn,int torow, int tocolumn){
    if((abs(fromrow-torow)==1 && abs(fromcolumn-tocolumn)==1)||(fromrow==torow && abs(tocolumn-fromcolumn)==1)||(fromcolumn==tocolumn && abs(torow-fromrow)==1)){
        return true;
    }else{
        return false;
    }
}

// this function to check the validity of the movement
bool check_valid_move(int fromrow,int fromcolumn,int torow,int tocolumn){
// check the validity of the black pawn
    if(game[fromrow][fromcolumn]=='P'){
        if(game[torow][tocolumn]=='R'||game[torow][tocolumn]=='N'||game[torow][tocolumn]=='B'||game[torow][tocolumn]=='Q'||game[torow][tocolumn]=='K'||game[torow][tocolumn]=='P'){
            validmove=false;
            return validmove;
        }else{
            validmove=black_pawn(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
// check the validity of the white pawn
    if(game[fromrow][fromcolumn]=='p'){
        if(game[torow][tocolumn]=='r'||game[torow][tocolumn]=='n'||game[torow][tocolumn]=='b'||game[torow][tocolumn]=='q'||game[torow][tocolumn]=='k'||game[torow][tocolumn]=='p'){
            validmove=false;
            return validmove;
        }else{
            validmove=white_pawn(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
// check the validity of the black rook
    if(game[fromrow][fromcolumn]=='R'){
        if(game[torow][tocolumn]=='R'||game[torow][tocolumn]=='N'||game[torow][tocolumn]=='B'||game[torow][tocolumn]=='Q'||game[torow][tocolumn]=='K'||game[torow][tocolumn]=='P'){
            validmove=false;
            return validmove;
        }else{
            validmove=Rook(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
// check the validity of the white rook
    if(game[fromrow][fromcolumn]=='r'){
        if(game[torow][tocolumn]=='r'||game[torow][tocolumn]=='n'||game[torow][tocolumn]=='b'||game[torow][tocolumn]=='q'||game[torow][tocolumn]=='k'||game[torow][tocolumn]=='p'){
            validmove=false;
            return validmove;
        }else{
            validmove=Rook(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
//check the validity of black bishop
    if(game[fromrow][fromcolumn]=='B'){
        if(game[torow][tocolumn]=='R'||game[torow][tocolumn]=='N'||game[torow][tocolumn]=='B'||game[torow][tocolumn]=='Q'||game[torow][tocolumn]=='K'||game[torow][tocolumn]=='P'){
            validmove=false;
            return validmove;
        }else{
            validmove=Bishop(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
//check the validity of white bishop
    if(game[fromrow][fromcolumn]=='b'){
        if(game[torow][tocolumn]=='r'||game[torow][tocolumn]=='n'||game[torow][tocolumn]=='b'||game[torow][tocolumn]=='q'||game[torow][tocolumn]=='k'||game[torow][tocolumn]=='p'){
            validmove=false;
            return validmove;
        }else{
            validmove=Bishop(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
    //check the validity of black knight
    if(game[fromrow][fromcolumn]=='N'){
        if(game[torow][tocolumn]=='R'||game[torow][tocolumn]=='N'||game[torow][tocolumn]=='B'||game[torow][tocolumn]=='Q'||game[torow][tocolumn]=='K'||game[torow][tocolumn]=='P'){
            validmove=false;
            return validmove;
        }else{
            validmove=knight(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
//check the validity of white knight
    if(game[fromrow][fromcolumn]=='n'){
        if(game[torow][tocolumn]=='r'||game[torow][tocolumn]=='n'||game[torow][tocolumn]=='b'||game[torow][tocolumn]=='q'||game[torow][tocolumn]=='k'||game[torow][tocolumn]=='p'){
            validmove=false;
            return validmove;
        }else{
            validmove=knight(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }

//check the validity of black queen
    if(game[fromrow][fromcolumn]=='Q'){
        if(game[torow][tocolumn]=='R'||game[torow][tocolumn]=='N'||game[torow][tocolumn]=='B'||game[torow][tocolumn]=='Q'||game[torow][tocolumn]=='K'||game[torow][tocolumn]=='P'){
            validmove=false;
            return validmove;
        }else{
            validmove=Queen(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
// check the validity of the white queen
    if(game[fromrow][fromcolumn]=='q'){
        if(game[torow][tocolumn]=='r'||game[torow][tocolumn]=='n'||game[torow][tocolumn]=='b'||game[torow][tocolumn]=='q'||game[torow][tocolumn]=='k'||game[torow][tocolumn]=='p'){
            validmove=false;
            return validmove;
        }else{
            validmove=Queen(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
// check the validity of the black king
    if(game[fromrow][fromcolumn]=='K'){
        if(game[torow][tocolumn]=='R'||game[torow][tocolumn]=='N'||game[torow][tocolumn]=='B'||game[torow][tocolumn]=='Q'||game[torow][tocolumn]=='K'||game[torow][tocolumn]=='P'){
            validmove=false;
            return validmove;
        }else{
            validmove= King(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
// check the validity of the white king
    if(game[fromrow][fromcolumn]=='k'){
        if(game[torow][tocolumn]=='r'||game[torow][tocolumn]=='n'||game[torow][tocolumn]=='b'||game[torow][tocolumn]=='q'||game[torow][tocolumn]=='k'||game[torow][tocolumn]=='p'){
            validmove=false;
            return validmove;
        }else{
            validmove=King(fromrow,fromcolumn,torow,tocolumn);
            return validmove;
        }
    }
//empty cell
    if((game[fromrow][fromcolumn]=='-')||(game[fromrow][fromcolumn]=='.')){
        validmove=false;
        return validmove;
    }
//remain in place
    if(fromrow==torow && fromcolumn==tocolumn){
        validmove=false;
        return validmove;
    }
}

//function for printing board
void Printing_board(){
    printf("\n");
    for (int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            printf("%c ",game[i][j]);
        }
        printf("\n");
    }
}

bool safe_my_king_white(){
    int kingrow,kingcolumn;

    for(int i=1; i<9; i++){                 //find my king
        for(int j=1; j<9; j++){
            if(game[i][j]=='k'){
                kingrow=i;
                kingcolumn=j;
                break;
            }
        }
    }

    for(int i=1; i<9; i++){                 // find if my king is checked by any black piece
        for(int j=1; j<9; j++){
            if(game[i][j]>='A' && game[i][j]<='Z'){
                if(check_valid_move(i,j,kingrow,kingcolumn)==true && Check_the_way(i,j,kingrow,kingcolumn)==true){
                    return false;
                    break;
                }
            }
        }
        if(i==8){
            return true;
        }
    }
}

bool safe_my_king_Black(){
    int kingrow,kingcolumn;

    for(int i=1; i<9; i++){                      //find my king
        for(int j=1; j<9; j++){
            if(game[i][j]=='K'){
                kingrow=i;
                kingcolumn=j;
                break;
            }
        }
    }


    for(int i=1; i<9; i++){                     // find if my king is checked by any white piece
        for(int j=1; j<9; j++){
            if(game[i][j]>='a' && game[i][j]<='z'){
                if(check_valid_move(i,j,kingrow,kingcolumn)==true && Check_the_way(i,j,kingrow,kingcolumn)==true){
                    return false;
                    break;
                }
            }
        }
        if(i==8){
            return true;
        }
    }
}

// take the step
void Move(int fromrow,int fromcolumn, int torow, int tocolumn,int turn){

    char  oldfrom=game[fromrow][fromcolumn];
    char  oldto=game[torow][tocolumn];

    takemove=check_valid_move(fromrow,fromcolumn,torow,tocolumn);
    clearpath=Check_the_way(fromrow,fromcolumn,torow,tocolumn);

if(takemove==true && clearpath==true){
    if(game[torow][tocolumn]=='.'||game[torow][tocolumn]=='-'){

        char x= game[torow][tocolumn];
        changed(x,turn);

            game[torow][tocolumn]=game[fromrow][fromcolumn];
            if((fromrow+fromcolumn)%2==0){
                game[fromrow][fromcolumn]='-';

            }else{
                game[fromrow][fromcolumn]='.';
            }


    if(turn%2!=0){
        stupidmovewhite=safe_my_king_white();
            if(stupidmovewhite==false){
                game[fromrow][fromcolumn]=oldfrom;
                game[torow][tocolumn]=oldto;
                printf("Your king will be checked , try another game\n");
                Printing_board();
                get_input(turn);
            }else{
                data(fromrow,fromcolumn,torow,tocolumn,turn);
                Printing_board();
                printf("Black eaten : ");
                for(int i=0 ; i<=index_black_eaten; i++){
                    printf("%c ",black_eaten[i]);}
                    printf("\n");
                    printf("White eaten : ");
                for(int j=0; j<=index_white_eaten; j++){
                    printf("%c ",white_eaten[j]);}
                    printf("\n");

                    if(!check(turn)){
                        if(Stalemate_black()){
                            printf("STALEMATE \n");
                            END=true;
                            }else{
                                if(Draw()){
                                printf("STALEMATE BY DRAW \n");
                                END=true;
                                }
                            }
                        }
                    }
                }

        if(turn%2==0){
            stupidmoveblack=safe_my_king_Black();
                if(stupidmoveblack==false){
                        game[fromrow][fromcolumn]=oldfrom;
                        game[torow][tocolumn]=oldto;
                        printf("Your king will be checked , try another game\n");
                        Printing_board();
                        get_input(turn);
                }else{
                    data(fromrow,fromcolumn,torow,tocolumn,turn);
                    Printing_board();
                    printf("Black eaten : ");
                    for(int i=0 ; i<=index_black_eaten; i++){
                        printf("%c ",black_eaten[i]);}
                        printf("\n");
                        printf("White eaten : ");
                    for(int j=0; j<=index_white_eaten; j++){
                        printf("%c ",white_eaten[j]);}
                        printf("\n");

                        if(!check(turn)){
                            if(Stalemate_white()){
                                printf("STALEMATE \n");
                                END=true;
                            }else{
                            if(Draw()){
                                printf("STALEMATE BY DRAW \n");
                                END=true;
                            }
                        }
                   }
                }
            }
        }else{
            if(turn%2!=0){

                black_eaten[index_black_eaten] =game[torow][tocolumn];
                changed(black_eaten[index_black_eaten],turn);
                data(fromrow,fromcolumn,torow,tocolumn,turn);
                game[torow][tocolumn]=game[fromrow][fromcolumn];
                index_black_eaten++;

                if((fromrow+fromcolumn%2)==0){
                    game[fromrow][fromcolumn]='-';
                }else{
                    game[fromrow][fromcolumn]='.';
                }

                stupidmovewhite=safe_my_king_white();
                if(stupidmovewhite==false){
                    game[fromrow][fromcolumn]=oldfrom;
                    game[torow][tocolumn]=oldto;
                    printf("Your king will be checked , try another game\n");
                    Printing_board();
                    get_input(turn);
                }else{
                    Printing_board();
                    printf("Black eaten : ");
                    for(int i=0 ; i<index_black_eaten; i++){
                        printf("%c ",black_eaten[i]);}
                        printf("\nWhite eaten : ");
                    for(int j=0; j<index_white_eaten; j++){
                        printf("%c ",white_eaten[j]);}
                        printf("\n");
                    if(!check(turn)){
                        if(Stalemate_black()){
                            printf("STALEMATE \n");
                            END=true;
                       }else{
                            if(Draw()){
                            printf("STALEMATE BY DRAW \n");
                            END=true;
                            }
                        }
                   }
                }
            }

            if(turn%2==0){
                white_eaten[index_white_eaten]= game[torow][tocolumn];
                changed(white_eaten[index_white_eaten],turn);

                data(fromrow,fromcolumn,torow,tocolumn,turn);                //

                game[torow][tocolumn]=game[fromrow][fromcolumn];
                index_white_eaten++;

                if((fromrow+fromcolumn)%2==0){
                    game[fromrow][fromcolumn]='-';
                }else{
                    game[fromrow][fromcolumn]='.';
                }

                stupidmoveblack=safe_my_king_Black();
                if(stupidmoveblack==false){
                    game[fromrow][fromcolumn]=oldfrom;
                    game[torow][tocolumn]=oldto;
                    printf("Your king will be checked , try another game\n");
                    Printing_board();
                    get_input(turn);
                }
                else{
                    Printing_board();
                    printf("Black eaten : ");
                    for(int i=0 ; i<index_black_eaten; i++){
                        printf("%c ",black_eaten[i]);}
                        printf("\n");
                        printf("White eaten : ");
                    for(int j=0; j<index_white_eaten; j++){
                        printf("%c ",white_eaten[j]);}
                        printf("\n");

                     if(!check(turn)){
                        if(Stalemate_white()){
                            printf("STALEMATE \n");
                            END=true;
                        }else{
                            if(Draw()){
                            printf("STALEMATE BY DRAW \n");
                            END=true;
                            }
                        }
                   }
                }
            }
        }

    }else{
        printf("NOT VALID MOVE\n");     //warning message
        get_input(turn);
    }
}

//this function to switch the char to the number of column
int turn_integer(char x)
{
    switch (x)
    {
    case 'A' :
        return 1;
        break;
    case 'B' :
        return 2;
        break;
    case 'C' :
        return 3;
        break;
    case 'D' :
        return 4;
        break;
    case 'E' :
        return 5;
        break;
    case 'F' :
        return 6;
        break;
    case 'G' :
        return 7;
        break;
    case 'H' :
        return 8;
        break;
    }
}

// function of get the step & check if it correct
void get_input(int turn)
{
    char tmp1,tmp2;
    int wrong=1;    //int variable to check if the input correct
    bool promoted;  //boolean variable to check if the move is a promotion or not
    do
    {

        printf("ENTER MOVE: ");
        scanf("%c%c%c%c",&fromcolumn,&tmp1,&tocolumn,&tmp2);
        while (getchar()!='\n');


        if(tmp1<'1'||tmp1>'8'||tmp2<'1'||tmp2>'8'){
            printf("NOT VALID POSITION\n");     //warning message
            wrong=1;
            continue;
        }else{
            //convert char to integer
            fromrow=tmp1-'0';
            torow=tmp2-'0';
        }
        if((fromrow<1||fromrow>8)||(torow<1||torow>8)||
                (fromcolumn!='A'&&fromcolumn!='B'&&fromcolumn!='C'&&fromcolumn!='D'&&fromcolumn!='E'&&fromcolumn!='F'&&fromcolumn!='G'&&fromcolumn!='H')||
                (tocolumn!='A'&&tocolumn!='B'&&tocolumn!='C'&&tocolumn!='D'&&tocolumn!='E'&&tocolumn!='F'&&tocolumn!='G'&&tocolumn!='H')){
            wrong=1;
            printf("NOT VALID POSITION\n");     //warning message
        }else{
            wrong=0;
            fromcolumn=turn_integer(fromcolumn);
            tocolumn=turn_integer(tocolumn);

            if(turn%2!=0){
                if(game[fromrow][fromcolumn]=='P'||game[fromrow][fromcolumn]=='R'||game[fromrow][fromcolumn]=='N'||game[fromrow][fromcolumn]=='B'
                        ||game[fromrow][fromcolumn]=='Q'||game[fromrow][fromcolumn]=='K'){
                    wrong=1;
                    printf("CAN'T MOVE BLACK PIECE\n");     //warning message
                }
            }
            if(turn%2==0){
                if(game[fromrow][fromcolumn]=='p'||game[fromrow][fromcolumn]=='r'||game[fromrow][fromcolumn]=='n'||game[fromrow][fromcolumn]=='b'
                        ||game[fromrow][fromcolumn]=='q'||game[fromrow][fromcolumn]=='k'){
                    wrong=1;
                    printf("CAN'T MOVE WHITE PIECE\n");     //warning message
                }
            }
        }
    }
    while(wrong==1);

    if(wrong==0)
    {
        promoted=promotion(fromrow,fromcolumn,torow,tocolumn,turn);
        if(promoted==false)
        {
            Move(fromrow,fromcolumn,torow,tocolumn,turn);
        }
    }
}

bool kingISsafe (int i,int j,int kingrow,int kingcolumn){
    if((check_valid_move(i,j,kingrow,kingcolumn)==true) && (Check_the_way(i,j,kingrow,kingcolumn)==true)){
        return false;
    }else{
        return true ;
    }
}

void checkMate(int fromrow,int fromcolumn,int torow,int tocolumn,int turn){
    END=true;
    int kingrow,kingcolumn;
    bool valid ;
    bool checkway;

    if((turn%2!=0)&&(safe_my_king_Black()==false)){ //black king is under check //
        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]=='K'){
                    kingrow=i;                   //king index//
                    kingcolumn=j;
                    break;
                }
            }
        }

        for (int i=1; i<9; i++){                ///capturing the attacker
            for(int j=1; j<9; j++){
                if ((game[i][j]>='A')&&(game[i][j]<='Z')){

                    valid =check_valid_move(i,j,attackerrow,attackercolumn);            ///check if any black piece can capture the attacker
                    checkway=Check_the_way(i,j,attackerrow,attackercolumn);

                    if((valid==true)&&(checkway==true)){
                            if(game[i][j]=='K'){
                            for(int m=1;m<9;m++){
                                for(int n=1;n<9;n++){
                                    if((game[m][n]>='a')&&(game[m][n]<='z')){
                                            game[attackerrow][attackercolumn]='K';
                                            valid=check_valid_move(m,n,attackerrow,attackercolumn);
                                            checkway=Check_the_way(m,n,attackerrow,attackercolumn);
                                            game[attackerrow][attackercolumn]=attackerpiece;
                                                if((valid==true)&&(checkway==true)){
                                                    END=true;
                                                    i=j=n=m=9;
                                                    break;
                                                    }
                                    }else{
                                        END=false;
                                        }
                                    }
                                }
                        }else{
                            END=false;
                            i=j=9;
                            break;
                            }
                        }
                    }
                }
            }

    for (int i=1; i<9; i++){                                //check if any black piece can block between the attacker & the king
        for(int j=1; j<9; j++){
            if ((game[i][j]>='A')&&(game[i][j]<='Z')){
                    for(int k=1; k<=8; k++){
                        for(int l=1; l<=8; l++){
                            valid =check_valid_move(i,j,k,l);
                            checkway=Check_the_way(i,j,k,l);
                            if((valid==true)&&(checkway==true)){
                                    char previousPOS= game[k][l];
                                           game[k][l]=game[i][j];
                                           game[i][j]=previousPOS;
                              if(Recheck(turn)==false){
                                    END = false ;
                                    game[i][j]=game[k][l];
                                    game[k][l]=previousPOS;
                                    i=j=k=l=9;
                                    break ;
                                } else {
                                         game[i][j]=game[k][l];
                                        game[k][l]=previousPOS;


                                    }
                            }
                        }
                    }
                }
            }
        }

    if(END==false){                                     //check if the king can move away to a safe position //
        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                valid=check_valid_move(kingrow,kingcolumn,i,j);
                checkway=Check_the_way(kingrow,kingcolumn,i,j);
                    if((valid==true)&&(checkway==true)){
                            game[kingrow][kingcolumn]=game[i][j];
                            game[i][j]='K';

                        if(kingISsafe(i,j,attackerrow,attackercolumn)==true){
                            END=false;
                            game[i][j]=game[kingrow][kingcolumn];
                            game[kingrow][kingcolumn]='K';
                            i=j=9;

                            break ;
                        }else {
                            game[i][j]=game[kingrow][kingcolumn];
                            game[kingrow][kingcolumn]='K';
                        }


                    }
                }
            }

        }

    if(END==true){
            printf("CHECK MATE \t WHITE WINS\n");

        }
    }

                                        // white king is checked //

    if((turn%2==0)&&(safe_my_king_white()==false)){                               //white king is under check //
        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                if(game[i][j]=='k'){
                    kingrow=i;                      //king index//
                    kingcolumn=j;
                    break;
                }
            }
        }

        for (int i=1; i<9; i++){                 //capturing the attacker //
            for(int j=1; j<9; j++){
                if ((game[i][j]>='a')&&(game[i][j]<='z')){
                    valid =check_valid_move(i,j,attackerrow,attackercolumn);    //check if any white piece can capture the attacker //
                    checkway=Check_the_way(i,j,attackerrow,attackercolumn);

                    if((valid==true)&&(checkway==true)){
                            if(game[i][j]=='k'){
                                for(int m=1;m<9;m++){
                                    for(int n=1;n<9;n++){
                                        if((game[m][n]>='A')&&(game[m][n]<='Z')){
                                            game[attackerrow][attackercolumn]='k';
                                            valid=check_valid_move(m,n,attackerrow,attackercolumn);
                                            checkway=Check_the_way(m,n,attackerrow,attackercolumn);
                                            game[attackerrow][attackercolumn]=attackerpiece;
                                                if((valid==true)&&(checkway==true)){
                                                    END=true;
                                                    i=j=n=m=9;
                                                    break;
                                                }
                                        }else{
                                            END=false;
                                        }
                                    }
                                }
                        }else{
                            END=false;
                            i=j=9;
                            break;
                            }
                        }
                    }
                }
            }

    for (int i=1; i<9; i++){                         //check if any white piece can block between the attacker & the king
        for(int j=1; j<9; j++){
                if((game[i][j]>='a')&&(game[i][j]<='z')){
                    for(int k=1; k<=8; k++){
                        for(int l=1; l<=8; l++){
                            valid =check_valid_move(i,j,k,l);
                            checkway=Check_the_way(i,j,k,l);
                            if((valid==true)&&(checkway==true)){
                                  /*  printf(" TURN =%d I=%d j=%d k=%d l=%d\n",turn,i,j,k,l);*/
                                    char previousPOS= game[k][l];
                                           game[k][l]=game[i][j];
                                           game[i][j]=previousPOS;
                                if(Recheck(turn)==false){

                                    END = false;

                                    game[i][j]=game[k][l];
                                    game[k][l]=previousPOS;
                                    i=j=k=l=9;
                                    break ;
                                    }else {
                                         game[i][j]=game[k][l];
                                        game[k][l]=previousPOS;


                                    }
                                }
                            }
                        }
                    }
                }
            }

   if(END==false){                                     //check if the king can move away to a safe position //
        for(int i=1; i<9; i++){
            for(int j=1; j<9; j++){
                valid=check_valid_move(kingrow,kingcolumn,i,j);
                checkway=Check_the_way(kingrow,kingcolumn,i,j);
                    if((valid==true)&&(checkway==true)){
                            game[kingrow][kingcolumn]=game[i][j];
                            game[i][j]='k';

                        if(kingISsafe(i,j,attackerrow,attackercolumn)==true){
                            END=false;
                            game[i][j]=game[kingrow][kingcolumn];
                            game[kingrow][kingcolumn]='k';
                            i=j=9;

                            break ;
                        }else {
                            game[i][j]=game[kingrow][kingcolumn];
                            game[kingrow][kingcolumn]='k';
                        }


                    }
                }
            }

        }

    if(END==true){
            printf("CHECK MATE \t BLACK WINS\n");
            }
        }
}

/// FUNCTION STORES THE MOVES
void data(int fromrow,int fromcolumn ,int torow ,int tocolumn ,int turn){
            history[turn-1][0]=fromcolumn;
            history[turn-1][1]=fromrow;
            history[turn-1][2]=tocolumn;
            history[turn-1][3]=torow;
}

/// FUNCTION STORES THE CHANGES WHICH HAS HAPPENED IN THE GAME SO WE CAN USE IT TO UNDO MOVE
void changed(char eat,int turn){
    change[turn-1][1]=eat;

}
/// FUNCTION TO MAKE UNDO
int undo(int turn){
    char redo;
    char UN ;
    if(promsuccess!=1){                 //MAKE SURE IF ITS PROMOTION CASE OR NOT
        game[history[turn-1][1]][history[turn-1][0]]=game[history[turn-1][3]][history[turn-1][2]];
        game[history[turn-1][3]][history[turn-1][2]]=change[turn-1][1];
        Printing_board();

    do{
    printf("to redo your move press 1,to continue the game press 0: ");
    scanf("%c",&redo);
    while(getchar()!='\n');
     if(redo!='1'&&redo!='0'){
                    printf("Unknown choice,try again\n");
                }
    }
    while(redo!='1' && redo!='0');

    if(redo=='1'){
            doneRedo=1;
            game[history[turn-1][3]][history[turn-1][2]]=game[history[turn-1][1]][history[turn-1][0]];
            game[history[turn-1][1]][history[turn-1][0]]=change[turn-1][1];
            turn++;
            Printing_board();
        }

    if (turn!=1){
        do{
                printf("to undo your move press 1, to continue game press 0: ");
                scanf("%c",&UN);
                while(getchar()!='\n') ;
                 if(UN!='1'&&UN!='0'){
                    printf("Unknown choice,try again\n");
                }
            }

            while (UN!='0'&&UN!='1');

        if (UN=='1'){
            turn= undo(turn-1);
        }
    }


    }else if(promsuccess==1){
            game[history[turn-1][1]][history[turn-1][0]]= change[turn-1][1];
            game[history[turn-1][3]][history[turn-1][2]]=undoCase;
            promsuccess=0;
            Printing_board();

        do{
                printf("to redo your move press 1,to continue the game press 0: ");
                scanf("%c",&redo);
                while(getchar()!='\n');
                 if(redo!='1'&&redo!='0'){
                    printf("Unknown choice,try again\n");
                }
            }

        while(redo!='1' && redo!='0');

               if(redo=='1'){
                    doneRedo=1;
                    game[history[turn-1][1]][history[turn-1][0]]=undoCase;
                    game[history[turn-1][3]][history[turn-1][2]]=replace;
                    turn++;
                    Printing_board();
               }


    if(turn!=1){
               do{
                printf("to undo your move press 1, to continue game press 0: ");
                scanf("%c",&UN);
                while(getchar()!='\n') ;
                 if(UN!='1'&&UN!='0'){
                    printf("Unknown choice,try again\n");
                }
            }

            while (UN!='0'&&UN!='1');

        if (UN=='1'){
            if (turn==promoturn+1){
                promsuccess=1;
                turn= undo(turn-1);
            }else{
                promsuccess=0;
                turn= undo(turn-1);
                    }
                }
            }
        }
    return turn ;
}

int main()
{
    int turn=1;                     // int variable to swap the game between white and black
    char gamesave;                  // char to control save the game
    char loadgame;                  // char to control load the game
    char UN ;                       // char to undo the game
    bool firsttime=true;            // boolean variable to check if the load is successful from the first time or not


    do{
        if(firsttime==false){
             printf("Unknown choice, try again\n");
            }
            printf("for load game press 1, for new game press 0: ");
            scanf("%c",&loadgame);
            while(getchar()!='\n') ;
            firsttime=false;
    }

    while (loadgame!='0' && loadgame!='1');

    if(loadgame=='1'){
        turn=Load_game();
        }

    printf("    CHESS GAME ");
    Printing_board();                          //function to print the board of the game

    // game's flow

    while(END==false && gamesave!='1'){

        if(turn%2!=0){

            printf("\nWhite's Turn\t");
            get_input(turn);

            do{
                printf("to undo your move press 1, to continue game press 0: ");
                scanf("%c",&UN);
                while(getchar()!='\n') ;
                if(UN!='1'&&UN!='0'){
                    printf("Unknown choice,try again\n");
                }
            }

            while (UN!='0'&&UN!='1');

             if(UN=='1'){
                turn =undo(turn);
                }
             if(UN=='0'){
                 turn++;
                }

            do{

                printf("To save your game press 1, to continue game press 0: ");     //message to ask the users if they want to save their game or not
                scanf("%c",&gamesave);
                while(getchar()!='\n') ;
                if(gamesave!='1'&&gamesave!='0'){
                    printf("Unknown choice,try again\n");
                }
            }
            while(gamesave!='1' && gamesave!='0');

            if(gamesave == '1'){
                Save_my_game(turn);
            }



        }else{
            printf("\nBlack's Turn\t");
            get_input(turn);

           do{
                printf("to undo your move press 1 , to continue game press 0:");
                scanf("%c",&UN);
                while(getchar()!='\n') ;
                 if(UN!='1'&&UN!='0'){
                    printf("Unknown choice,try again\n");
                }
            }
            while (UN!='0'&&UN!='1');

             if(UN=='1'){
                turn =undo(turn);
                }
             if(UN=='0'){
                 turn++;
                }

             do{

                printf("To save your game press 1, to continue game press 0: ");     //message to ask the users if they want to save their game or not
                scanf("%c",&gamesave);
                while(getchar()!='\n') ;
                 if(gamesave!='1'&&gamesave!='0'){
                    printf("Unknown choice,try again\n");
                }

            }
            while(gamesave!='1' && gamesave!='0');

            if(gamesave == '1'){
                Save_my_game(turn);
            }
        }
    }

    if (END==true){
        printf("THE GAME IS OVER");                           //message that tells the 2 players that the game ends
    }
        return 0;
}
