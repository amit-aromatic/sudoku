//sudoku 4 - The Stand Alone File  : The solver solves by permutations
// the solver is improved slvsudk4
// solver can find alternate solutions

#include<conio.h>
#include<stdio.h>
#include<iostream.h>
#include<stdlib.h>
#include<ctype.h>
#include"graphics.cpp"
#include"f_permut.cpp"

void playsudoku_program();
void solvesudoku_program();

//interpret : converts the input characters ( sq and pos ) from
//            numeric keypad into the game coordinates (0 to 8)
//intrp_fill: helps interpret
//reveal    : converts the x and y coordinates (ranging b/w 0 t0 2)
//           of nth (n ranging from 0 to 8) square into game ccordinates (0-8)

void mk_rand_array(char []);
void mk_board(char [][9],char []);
void rearg_board(char [][9]);
void squares_to_game(char [][3][3],char [][9]);
void mk_solvable_game(char [][9]);
void mk_dummy(char[][9],char[][9]);
void display_col(char[][9],char [][9]);

void mk_squares(char [][3][3],char [][9]);
void display(char [][9]);
void interpret(int [],char,char);
void intrp_fill(int[][3],int[][3],int[],int[]);
void reveal_rc(int [],int,int,int);
void initialise_possibilities(char[][3][3][9]);

int solvable(char [][9]);
int check(char [][9]);
int check_0(char [][9]);

void filterpermutations(char [][9],char [][3][3],char [][3][3]);
void make_ordindex(int [], float []);

void show_message();

void main()
{
  char choice;

  input_again_main:
  clrscr();
  cout<<"\n\n\n				S U D O K U\n\n\n\n";
  cout<<"Press 1 : To play Sudoku               (ie. for you to solve one)\n"
      <<"      2 : To solve a Sudoku            (ie. you want computer to solve one)\n"
      <<"      3 : To read instructions to play (IMPORTANT)\n"
      <<"      4 : To exit : ";

  choice=getche();

 switch(choice)
  {
   case '1':
    playsudoku_program();
    break;
   case '2':
    solvesudoku_program();
    break;
   case '3':
    show_message();
    goto input_again_main;
   case '4':
    cbab(); cbab(); exit(0);
 default:
    goto input_again_main;
 }
}
/****************************************************************************/
/*			   PLAYSUDOKU PROGRAM                               */
/*               copy paste from option play of old sudoku.cpp              */
/*              (with minor adjustment for exit game option 'e')            */
/****************************************************************************/

void playsudoku_program()
{
    int win=1;
    char board[9][9],array[9],square[9][3][3],
	 game[9][9],dummy_g[9][9],
	 sq,pos,d;
    int r,c,rowcol[2];
	//array generates board(solution) from which game( by now
	// a 'solved, problem)
	//is made and played (solved,ie. game is what which when
	// made incomplete is played by the player )
    clrscr();

   mk_rand_array(array);
   //for(int z=0;z<9;z++) array[z]=49+z;   //+++++++++++++++++++++++
   mk_board(board,array);
   rearg_board(board);
   mk_squares(square,board);
   squares_to_game(square,game);
   mk_solvable_game(game);
   mk_dummy(game,dummy_g);

   do{
    input_again_case1:
    clrscr();
    display_col(game,dummy_g);
    cout<<"Press 0,0,0 and then any key to submit the game or to see solution\n"
	<<"      e to exit\n";
    hline();
    cout<<"\nSelect square : ";
     sq=getche();
    switch(sq)
     {
      case '7':
      case '8':
      case '9':
      case '4':
      case '5':
      case '6':
      case '1':
      case '2':
      case '3':
      case '0':
      case '.':
       break;
      case 'e':
      case 'E':
       cbab(); exit(0);
      default :
       cout<<" Error ! Please enter again.\n\nPRESS ANY KEY TO CONTINUE...";
       getch();
       goto input_again_case1;
     }
    cout<<"\nSelect position : ";
    pos=getche();
    switch(pos)
     {
      case '7':
      case '8':
      case '9':
      case '4':
      case '5':
      case '6':
      case '1':
      case '2':
      case '3':
      case '0':
      case '.':
       break;

      case 'e':
      case 'E':
       cbab(); exit(0);
      default :
       cout<<" Error ! Please enter again.\n\nPRESS ANY KEY TO CONTINUE...";
       getch();
       goto input_again_case1;
     }
    interpret(rowcol,sq,pos);
    r=rowcol[0]; c=rowcol[1];
    //cout<<"\naa:"<<r<<","<<c<<endl;

   if(!(sq=='0'&&pos=='0'))
    {
     if(dummy_g[r][c]=='L')
      {
       cout<<" The chosen position is LOCKED !!! Enter again.\n\nPRESS ANY KEY TO CONTINUE...";
       getch();
       goto input_again_case1;
      }
     }

    cout<<"\nEnter digit : ";
    d=getche();
    switch(d)
     {
      case '7':
      case '8':
      case '9':
      case '4':
      case '5':
      case '6':
      case '1':
      case '2':
      case '3':
      case '0':
      case '.':
       break;

      case 'e':
      case 'E':
       cbab(); exit(0);
      default :
       cout<<" Error ! Please enter again.\n\nPRESS ANY KEY TO CONTINUE...";
       getch();
       goto input_again_case1;
     }
    if(!( sq=='0' && pos=='0' && d=='0' ))
     {
     if(isdigit(d))
      {
       game[r][c]=d;
      }
      else if(d=='.')
      {
       game[r][c]=d;
      }
      else;
     }
    }while( !(sq=='0' && pos=='0' && d=='0' ));

   getch();
   for(int a=0;a<9;a++)
    for(int b=0;b<9;b++)
     {
      if(game[a][b]!=board[a][b])
       {
	win=0;
	goto decide;
       }
     }

    decide:

    if(win)
     {
      cout<<"\n\nSudoku Solved !";
      getch();
      clrscr();
      display_col(game,dummy_g);
      //display_col(board,dummy_g);
     }
    else
     {
      cout<<"\n\nSolution Incorrect.\n\nPress any key to view correct solution";
      getch();
      clrscr();
      display_col(game,dummy_g);
      display_col(board,dummy_g);
     }

    getch();
    return;
}
/****************************************************************************/
/*			  SOLVESUDOKU PROGRAM                               */
/*                 copy paste of main of slvsdku4.cpp                       */
/****************************************************************************/

void solvesudoku_program()
{
 char game[9][9],dummy[9][9],missing[9],present[9],
      possibilities[9][3][3][9],square[9][3][3],square_dum[9][3][3];
 char d,sq,pos,considered_dig,ch;
 int i,j,k,t,l,m,p,q,r,c,rowcol[2],considered_sq,flag_r,flag_c,
     no_of_possibilities,notsolved,chk,startrow,endrow,startcol,endcol;
 int xsqlimits[9][2], ysqlimits[9][2], ordindex[9];
 char temp[9],temp2[2];

 float i1,i2,i3,i4,i5,i6,i7,i8,i9,noffilteredpermutations[9],nofsol;

 static char *filename[]=
     {
      "1.txt",
      "2.txt",
      "3.txt",
      "4.txt",
      "5.txt",
      "6.txt",
      "7.txt",
      "8.txt",
      "9.txt"
     };
 xsqlimits[0][0] = 0; xsqlimits[0][1] = 2;
 xsqlimits[1][0] = 3; xsqlimits[1][1] = 5;
 xsqlimits[2][0] = 6; xsqlimits[2][1] = 8;
 xsqlimits[3][0] = 0; xsqlimits[3][1] = 2;
 xsqlimits[4][0] = 3; xsqlimits[4][1] = 5;
 xsqlimits[5][0] = 6; xsqlimits[5][1] = 8;
 xsqlimits[6][0] = 0; xsqlimits[6][1] = 2;
 xsqlimits[7][0] = 3; xsqlimits[7][1] = 5;
 xsqlimits[8][0] = 6; xsqlimits[8][1] = 8;

 ysqlimits[0][0] = 0; ysqlimits[0][1] = 2;
 ysqlimits[1][0] = 0; ysqlimits[1][1] = 2;
 ysqlimits[2][0] = 0; ysqlimits[2][1] = 2;
 ysqlimits[3][0] = 3; ysqlimits[3][1] = 5;
 ysqlimits[4][0] = 3; ysqlimits[4][1] = 5;
 ysqlimits[5][0] = 3; ysqlimits[5][1] = 5;
 ysqlimits[6][0] = 6; ysqlimits[6][1] = 8;
 ysqlimits[7][0] = 6; ysqlimits[7][1] = 8;
 ysqlimits[8][0] = 6; ysqlimits[8][1] = 8;

 FILE *fp,*fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp7,*fp8,*fp9;

 clrscr();
 printf("                         SUDOKU    SOLVER\nCan find Alternate Solutions.\n\n");
 /****************** initialization **********************/

 for( i=0;i<9;i++)
 for( j=0;j<9;j++)
 { game[i][j]='.'; dummy[i][j]='.'; }
 nofsol=0;

 /******************** input *****************************/


 do{
    clrscr();
    printf("                         SUDOKU    SOLVER\nCan find Alternate Solutions.\n\n");
    display_col(game,dummy);
    cout<<"Press 0,0,0 to submit the game for solution\n"
	<<"      e to exit\n";
    hline();
    input_again:
    cout<<"\nSelect square : ";
     sq=getche();
    switch(sq)
     {
      case '7':
      case '8':
      case '9':
      case '4':
      case '5':
      case '6':
      case '1':
      case '2':
      case '3':
      case '0':
      case '.':
       break;
      case 'e':
       goto end;
      default :
       cout<<" Error ! Please enter again.";
       goto input_again;
     }


    cout<<"\nSelect position : ";
    pos=getche();
    switch(pos)
     {
      case '7':
      case '8':
      case '9':
      case '4':
      case '5':
      case '6':
      case '1':
      case '2':
      case '3':
      case '0':
      case '.':
       break;
      case '-':
       goto input_again;
      case 'e':
       goto end;
      default :
       cout<<" Error ! Please enter again.";
       goto input_again;
     }


    interpret(rowcol,sq,pos);
    r=rowcol[0]; c=rowcol[1];
    //cout<<"\ninterpret:"<<r<<","<<c<<endl;


    cout<<"\nEnter digit : ";
    d=getche();
    switch(d)
     {
      case '7':
      case '8':
      case '9':
      case '4':
      case '5':
      case '6':
      case '1':
      case '2':
      case '3':
      case '0':
      case '.':
       break;
      case '-':
       goto input_again;
      case 'e':
       goto end;
      default :
       cout<<" Error ! Please enter again.";
       goto input_again;
     }



    if(!( sq=='0' || pos=='0' || d=='0' ))
     {
     if(isdigit(d))
      {
       game[r][c]=d;
       dummy[r][c]='L';
      }
      else if(d=='.')
      {
       game[r][c]=d;
       dummy[r][c]='.';
      }
      else;
     }
    }while( !(sq=='0' || pos=='0' || d=='0' ));
 clrscr();
 printf("                         SUDOKU    SOLVER\nCan find Alternate solutions.\n\n");
 //************* test input start: only for testing purpose. Reads sudoku
 // from a text file sudoku.txt in which digits are written in 9X9 array ////

/*
 FILE *fptest;
 char testch[2];
 fptest=fopen("sudoku.txt","r");
 for(i=0;i<9;i++)
  {
   for(j=0;j<9;j++)
    {
     fscanf(fptest,"%s",testch);
     d=testch[0];
     if(isdigit(d))
      {
       game[i][j]=d;
       dummy[i][j]='L';
      }
      else if(d=='.')
      {
       game[i][j]=d;
       dummy[i][j]='.';
      }
    }
   fscanf(fptest,"\n");
  }
 fclose(fptest);
*/

  /************* test input finish ******************************/
 /////////////////////////////////////////////////////////////////

 mk_squares(square,game);
 mk_squares(square_dum,dummy);
 display_col(game,dummy);
 //getch();
 chk=check(game);
    if (chk==1)
     {
      cout<<"\n\nSolved!";
      getch();
      goto end;
     }

 //************************* solution ********************************
 cout<<"Please Wait... Generating Permutations of the missing digits...\n";

 char missing_all [9][9];
 int nofmissing [9];

 for(i=0;i<9;i++)
  {
   nofmissing[i]=0;
   for(j=0;j<9;j++)
    {
     missing_all[i][j]='a';
    }
  }

 for(considered_sq=0;considered_sq<9;considered_sq++)
 {  // for loop 1: analyse every square
  t=0; int a=0;         // t=no. of missing digits in square & a=present

  for(i=0;i<3;i++)
   for(j=0;j<3;j++)
    {
     if(square[considered_sq][i][j]>=49&&square[considered_sq][i][j]<=57)
      {
       present[a++]=square[considered_sq][i][j];
      }
     }

   for(i=1;i<=9;i++)
    {
     int found=0;
     for(j=0;j<a;j++)
      {
       if(present[j]==i+48) { found=1; break; }
      }
     if(!found) missing_all[considered_sq][t++]=i+48;
    }
    nofmissing[considered_sq]=t;
  }//for loop 1 ends
//>>
  /*
  for(i=0;i<9;i++)
   {
    cout<<endl;
    for(j=0;j<nofmissing[i];j++)
     {
      cout<<missing_all[i][j];
     }
    }*/
//>>
  for(i=0;i<9;i++)
   {
    for(j=0;j<nofmissing[i];j++)
     {
      temp[j]=missing_all[i][j];
     }
     //cout<<"\nMissing in square "<<i<<" : "<<nofmissing[i];
     fpermut(temp,filename[i],nofmissing[i]);
   }

 cout<<"All Permutations generated and Files Written...\n\nNow Filtering them according to consistency to reduce their number...";
 //getch();

 filterpermutations(game,square,square_dum);
 cout<<"\nPermutations Filtered and Files Re-written...\nNumber of Leftover Filtered permutations : (squarewise)\n\n"; //getch();

 for(i=0;i<9;i++)
  {
   float w=0;  char tocount [20];
   fp=fopen(filename[i],"r");
   if(fp==NULL)  goto afterwhile;
   while(!feof(fp))
    {
     fscanf(fp," %[^\n]",tocount);
     w++;
    }
   w--;
   fclose(fp);
   afterwhile:

   noffilteredpermutations[i]=w;
   cout<<noffilteredpermutations[i]<<", ";
  }
  //getch();
/*
     switch(int(i1))
      {
       case 0:
	startrow=0; endrow=2;
	startcol=0; endcol=2;
	break;
       case 1:
	startrow=0; endrow=2;
	startcol=3; endcol=5;
	break;
       case 2:
	startrow=0; endrow=2;
	startcol=6; endcol=8;
	break;
       case 3:
	startrow=3; endrow=5;
	startcol=0; endcol=2;
	break;
       case 4:
	startrow=3; endrow=5;
	startcol=3; endcol=5;
	break;
       case 5:
	startrow=3; endrow=5;
	startcol=6; endcol=8;
	break;
       case 6:
	startrow=6; endrow=8;
	startcol=0; endcol=2;
	break;
       case 7:
	startrow=6; endrow=8;
	startcol=3; endcol=5;
	break;
       case 8:
	startrow=6; endrow=8;
	startcol=6; endcol=8;
	break;
      }

     for(i=startrow;i<=endrow;i++)
      {
       for(j=startcol;j<=endcol;j++)
       {
	if(dummy[i][j]=='.')
	 {
	  game[i][j]=temp[t++];
	  dummy[i][j]='L';
	 }
       }
      }
*/

 for(i1=0;i1<9;i1++)
  {
   if(noffilteredpermutations[i1]==0)
    {
     noffilteredpermutations[i1]=1; // it is necessary to enter nested loops below
    }
  }

  // ------now sorting noffiltered ---
 make_ordindex(ordindex, noffilteredpermutations);
 //cout<<endl;
 //for(i=0;i<9;i++) { cout<<" "<<ordindex[i]; }                 getch();
 //
//>>
  cout<<"\nNow trying these permutations to reach solution...\n";

  gotoxy(35,3); printf("Please wait...");
  gotoxy(35,4); printf("Time taken depends heavily on nature of clues");
  gotoxy(35,5); printf("given in sudoku than on no. of permutations.");

  fp1=fopen(filename[ordindex[0]],"r");                                   //лллллллллл

//  for(i1=0;(i1<factorial(nofmissing[0]) && !chk);i1++)
  for(i1=0;(i1<noffilteredpermutations[ordindex[0]] && !chk);i1++)        //лллллллллл
   {
    //cout<<"\n******************\n"<<noffilteredpermutations[ordindex[0]];
    if(!(fp1==NULL))
    {
    for(j=0;j<nofmissing[ordindex[0]];j++)                                //лллллллллл
     {
       fscanf(fp1,"%s",temp2);
       temp[j]=temp2[0];
     }
    t=0;

    for(i=ysqlimits[ ordindex[0] ][0];i<=ysqlimits[ ordindex[0] ][1];i++)                                           //лллллллллл
     {
      for(j=xsqlimits[ ordindex[0] ][0];j<=xsqlimits[ ordindex[0] ][1];j++)                                         //лллллллллл
      {
       if(dummy[i][j]=='.')
	{
	 game[i][j]=temp[t++];
	}
      }
     }
    fscanf(fp1,"\n");
    }

    chk=check(game);
    if(check_0(game)) continue;

    if (chk==1)
     {
      nofsol++;
      gotoxy(1,4);  display_col(game,dummy);
      gotoxy(35,7); cout<<"Solved!"; printf("  Solution no. %g",nofsol);
      gotoxy(35,9); cout<<"Press N: next sol or any other key: exit";
      ch=getch();
      if(ch=='n' || ch =='N') { chk=0;gotoxy(35,9); cout<<"                                        "; }
      else goto end;
     }

  fp2=fopen(filename[ordindex[1]],"r");
//  for(i2=0;(i2<factorial(nofmissing[1]) && !chk);i2++)
  for(i2=0;(i2<noffilteredpermutations[ordindex[1]] && !chk);i2++)
   {
    if(!(fp2==NULL))
    {
    for(j=0;j<nofmissing[ordindex[1]];j++)
     {
       fscanf(fp2,"%s",temp2);
       temp[j]=temp2[0];
     }
    t=0;

    for(i=ysqlimits[ ordindex[1] ][0];i<=ysqlimits[ ordindex[1] ][1];i++)
     {
      for(j=xsqlimits[ ordindex[1] ][0];j<=xsqlimits[ ordindex[1] ][1];j++)
      {
       if(dummy[i][j]=='.')
	{
	 game[i][j]=temp[t++];
	}
      }
     }
    fscanf(fp2,"\n");
    }

    chk=check(game);
    if(check_0(game)) goto endofloop2;

    if (chk==1)
     {
      nofsol++;
      gotoxy(1,4);  display_col(game,dummy);
      gotoxy(35,7); cout<<"Solved!"; printf("  Solution no. %g",nofsol);
      gotoxy(35,9); cout<<"Press N: next sol or any other key: exit";
      ch=getch();
      if(ch=='n' || ch =='N') { chk=0;gotoxy(35,9); cout<<"                                        "; }
      else goto end;
     }

  fp3=fopen(filename[ordindex[2]],"r");
//  for(i3=0;(i3<factorial(nofmissing[2]) && !chk);i3++)
  for(i3=0;(i3<noffilteredpermutations[ordindex[2]] && !chk);i3++)
   {
    if(!(fp3==NULL))
    {
    for(j=0;j<nofmissing[ordindex[2]];j++)
     {
       fscanf(fp3,"%s",temp2);
       temp[j]=temp2[0];
     }
    t=0;

    for(i=ysqlimits[ ordindex[2] ][0];i<=ysqlimits[ ordindex[2] ][1];i++)
     {
      for(j=xsqlimits[ ordindex[2] ][0];j<=xsqlimits[ ordindex[2] ][1];j++)
      {
       if(dummy[i][j]=='.')
	{
	 game[i][j]=temp[t++];
	}
      }
     }
    fscanf(fp3,"\n");
    }

    chk=check(game);
    if(check_0(game)) goto endofloop3;

    if (chk==1)
     {
      nofsol++;
      gotoxy(1,4);  display_col(game,dummy);
      gotoxy(35,7); cout<<"Solved!"; printf("  Solution no. %g",nofsol);
      gotoxy(35,9); cout<<"Press N: next sol or any other key: exit";
      ch=getch();
      if(ch=='n' || ch =='N') { chk=0;gotoxy(35,9); cout<<"                                        "; }
      else goto end;
     }

  fp4=fopen(filename[ordindex[3]],"r");
//  for(i4=0;(i4<factorial(nofmissing[3]) && !chk);i4++)
  for(i4=0;(i4<noffilteredpermutations[ordindex[3]] && !chk);i4++)
   {
    if(!(fp4==NULL))
    {
    for(j=0;j<nofmissing[ordindex[3]];j++)
     {
       fscanf(fp4,"%s",temp2);
       temp[j]=temp2[0];
     }
    t=0;

    for(i=ysqlimits[ ordindex[3] ][0];i<=ysqlimits[ ordindex[3] ][1];i++)
     {
      for(j=xsqlimits[ ordindex[3] ][0];j<=xsqlimits[ ordindex[3] ][1];j++)
      {
       if(dummy[i][j]=='.')
	{
	 game[i][j]=temp[t++];
	}
      }
     }
    fscanf(fp4,"\n");
    }

    chk=check(game);
    if(check_0(game)) goto endofloop4;

    if (chk==1)
     {
      nofsol++;
      gotoxy(1,4);  display_col(game,dummy);
      gotoxy(35,7); cout<<"Solved!"; printf("  Solution no. %g",nofsol);
      gotoxy(35,9); cout<<"Press N: next sol or any other key: exit";
      ch=getch();
      if(ch=='n' || ch =='N') { chk=0;gotoxy(35,9); cout<<"                                        "; }
      else goto end;
     }

  fp5=fopen(filename[ordindex[4]],"r");
 // for(i5=0;(i5<factorial(nofmissing[4]) && !chk);i5++)
  for(i5=0;(i5<noffilteredpermutations[ordindex[4]] && !chk);i5++)
   {
    if(!(fp5==NULL))
    {
    for(j=0;j<nofmissing[ordindex[4]];j++)
     {
       fscanf(fp5,"%s",temp2);
       temp[j]=temp2[0];
     }
    t=0;

    for(i=ysqlimits[ ordindex[4] ][0];i<=ysqlimits[ ordindex[4] ][1];i++)
     {
      for(j=xsqlimits[ ordindex[4] ][0];j<=xsqlimits[ ordindex[4] ][1];j++)
      {
       if(dummy[i][j]=='.')
	{
	 game[i][j]=temp[t++];
	}
      }
     }
    fscanf(fp5,"\n");
    }

    chk=check(game);
    if(check_0(game)) goto endofloop5;

    if (chk==1)
     {
      nofsol++;
      gotoxy(1,4);  display_col(game,dummy);
      gotoxy(35,7); cout<<"Solved!"; printf("  Solution no. %g",nofsol);
      gotoxy(35,9); cout<<"Press N: next sol or any other key: exit";
      ch=getch();
      if(ch=='n' || ch =='N') { chk=0;gotoxy(35,9); cout<<"                                        "; }
      else goto end;
     }

  fp6=fopen(filename[ordindex[5]],"r");
//  for(i6=0;(i6<factorial(nofmissing[5]) && !chk);i6++)
  for(i6=0;(i6<noffilteredpermutations[ordindex[5]] && !chk);i6++)
   {
    if(!(fp6==NULL))
    {
    for(j=0;j<nofmissing[ordindex[5]];j++)
     {
       fscanf(fp6,"%s",temp2);
       temp[j]=temp2[0];
     }
    t=0;

    for(i=ysqlimits[ ordindex[5] ][0];i<=ysqlimits[ ordindex[5] ][1];i++)
     {
      for(j=xsqlimits[ ordindex[5] ][0];j<=xsqlimits[ ordindex[5] ][1];j++)
      {
       if(dummy[i][j]=='.')
	{
	 game[i][j]=temp[t++];
	}
      }
     }
    fscanf(fp6,"\n");
    }

    chk=check(game);
    if(check_0(game)) goto endofloop6;

    if (chk==1)
     {
      nofsol++;
      gotoxy(1,4);  display_col(game,dummy);
      gotoxy(35,7); cout<<"Solved!"; printf("  Solution no. %g",nofsol);
      gotoxy(35,9); cout<<"Press N: next sol or any other key: exit";
      ch=getch();
      if(ch=='n' || ch =='N') { chk=0;gotoxy(35,9); cout<<"                                        "; }
      else goto end;
     }

  fp7=fopen(filename[ordindex[6]],"r");
//  for(i7=0;(i7<factorial(nofmissing[6]) && !chk);i7++)
  for(i7=0;(i7<noffilteredpermutations[ordindex[6]] && !chk);i7++)
   {
    if(!(fp7==NULL))
    {
    for(j=0;j<nofmissing[ordindex[6]];j++)
     {
       fscanf(fp7,"%s",temp2);
       temp[j]=temp2[0];
     }
    t=0;

    for(i=ysqlimits[ ordindex[6] ][0];i<=ysqlimits[ ordindex[6] ][1];i++)
     {
      for(j=xsqlimits[ ordindex[6] ][0];j<=xsqlimits[ ordindex[6] ][1];j++)
      {
       if(dummy[i][j]=='.')
	{
	 game[i][j]=temp[t++];
	}
      }
     }
    fscanf(fp7,"\n");
    }

    chk=check(game);
    if(check_0(game)) goto endofloop7;

    if (chk==1)
     {
      nofsol++;
      gotoxy(1,4);  display_col(game,dummy);
      gotoxy(35,7); cout<<"Solved!"; printf("  Solution no. %g",nofsol);
      gotoxy(35,9); cout<<"Press N: next sol or any other key: exit";
      ch=getch();
      if(ch=='n' || ch =='N') { chk=0;gotoxy(35,9); cout<<"                                        "; }
      else goto end;
     }

  fp8=fopen(filename[ordindex[7]],"r");
//  for(i8=0;(i8<factorial(nofmissing[7]) && !chk);i8++)
  for(i8=0;(i8<noffilteredpermutations[ordindex[7]] && !chk);i8++)
   {
    if(!(fp8==NULL))
    {
    for(j=0;j<nofmissing[ordindex[7]];j++)
     {
       fscanf(fp8,"%s",temp2);
       temp[j]=temp2[0];
     }
    t=0;

    for(i=ysqlimits[ ordindex[7] ][0];i<=ysqlimits[ ordindex[7] ][1];i++)
     {
      for(j=xsqlimits[ ordindex[7] ][0];j<=xsqlimits[ ordindex[7] ][1];j++)
      {
       if(dummy[i][j]=='.')
	{
	 game[i][j]=temp[t++];
	}
      }
     }
    fscanf(fp8,"\n");
    }

    chk=check(game);
    if(check_0(game)) goto endofloop8;

    if (chk==1)
     {
      nofsol++;
      gotoxy(1,4);  display_col(game,dummy);
      gotoxy(35,7); cout<<"Solved!"; printf("  Solution no. %g",nofsol);
      gotoxy(35,9); cout<<"Press N: next sol or any other key: exit";
      ch=getch();
      if(ch=='n' || ch =='N') { chk=0;gotoxy(35,9); cout<<"                                        "; }
      else goto end;
     }

  fp9=fopen(filename[ordindex[8]],"r");
//  for(i9=0;(i9<factorial(nofmissing[8]) && !chk);i9++)
  for(i9=0;(i9<noffilteredpermutations[ordindex[8]] && !chk);i9++)
   {
    if(!(fp9==NULL))
    {
    for(j=0;j<nofmissing[ordindex[8]];j++)
     {
       fscanf(fp9,"%s",temp2);
       temp[j]=temp2[0];
     }
    t=0;

    for(i=ysqlimits[ ordindex[8] ][0];i<=ysqlimits[ ordindex[8] ][1];i++)
     {
      for(j=xsqlimits[ ordindex[8] ][0];j<=xsqlimits[ ordindex[8] ][1];j++)
      {
       if(dummy[i][j]=='.')
	{
	 game[i][j]=temp[t++];
	}
      }
     }
    fscanf(fp9,"\n");
    }

    chk=check(game);
    if(check_0(game)) goto endofloop9;

    if (chk==1)
     {
      nofsol++;
      gotoxy(1,4);  display_col(game,dummy);
      gotoxy(35,7); cout<<"Solved!"; printf("  Solution no. %g",nofsol);
      gotoxy(35,9); cout<<"Press N: next sol or any other key: exit";
      ch=getch();
      if(ch=='n' || ch =='N') { chk=0;gotoxy(35,9); cout<<"                                        "; }
      else goto end;
     }

    //cout<<"\nIn loop 9";
   gotoxy(2,22); printf("                                        				       "); gotoxy(2,22);   printf("%g %g %g %g %g %g %g %g %g ",i1,i2,i3,i4,i5,i6,i7,i8,i9);
   endofloop9:
   if(i9==noffilteredpermutations[ordindex[8]]-1) { for(i=ysqlimits[ ordindex[8] ][0];i<=ysqlimits[ ordindex[8] ][1];i++) for(j=xsqlimits[ ordindex[8] ][0];j<=xsqlimits[ ordindex[8] ][1];j++)  if(dummy[i][j]=='.') game[i][j]='.'; }
   }
    //cout<<"\nIn loop 8";
   gotoxy(2,22); printf("                                        				       "); gotoxy(2,22);   printf("%g %g %g %g %g %g %g %g ",i1,i2,i3,i4,i5,i6,i7,i8);
   endofloop8:
   if(i8==noffilteredpermutations[ordindex[7]]-1) { for(i=ysqlimits[ ordindex[7] ][0];i<=ysqlimits[ ordindex[7] ][1];i++) for(j=xsqlimits[ ordindex[7] ][0];j<=xsqlimits[ ordindex[7] ][1];j++)  if(dummy[i][j]=='.') game[i][j]='.'; }
   fclose(fp9);
   }
    //cout<<"\nIn loop 7";
   gotoxy(2,22); printf("                                        				       "); gotoxy(2,22);   printf("%g %g %g %g %g %g %g ",i1,i2,i3,i4,i5,i6,i7);
   endofloop7:
   if(i7==noffilteredpermutations[ordindex[6]]-1) { for(i=ysqlimits[ ordindex[6] ][0];i<=ysqlimits[ ordindex[6] ][1];i++) for(j=xsqlimits[ ordindex[6] ][0];j<=xsqlimits[ ordindex[6] ][1];j++)  if(dummy[i][j]=='.') game[i][j]='.'; }
   fclose(fp8);
   }
    //cout<<"\nIn loop 6";
   gotoxy(2,22); printf("                                        				       "); gotoxy(2,22);   printf("%g %g %g %g %g %g ",i1,i2,i3,i4,i5,i6);
   endofloop6:
   if(i6==noffilteredpermutations[ordindex[5]]-1) { for(i=ysqlimits[ ordindex[5] ][0];i<=ysqlimits[ ordindex[5] ][1];i++) for(j=xsqlimits[ ordindex[5] ][0];j<=xsqlimits[ ordindex[5] ][1];j++)  if(dummy[i][j]=='.') game[i][j]='.'; }
   fclose(fp7);
   }
    //cout<<"\nIn loop 5";
   gotoxy(2,22); printf("                                        				       "); gotoxy(2,22);   printf("%g %g %g %g %g ",i1,i2,i3,i4,i5);
   endofloop5:
   if(i5==noffilteredpermutations[ordindex[4]]-1) { for(i=ysqlimits[ ordindex[4] ][0];i<=ysqlimits[ ordindex[4] ][1];i++) for(j=xsqlimits[ ordindex[4] ][0];j<=xsqlimits[ ordindex[4] ][1];j++)  if(dummy[i][j]=='.') game[i][j]='.'; }
   fclose(fp6);
   }
    //cout<<"\nIn loop 4";
   gotoxy(2,22); printf("                                        				       "); gotoxy(2,22);   printf("%g %g %g %g ",i1,i2,i3,i4);
   endofloop4:
   if(i4==noffilteredpermutations[ordindex[3]]-1) { for(i=ysqlimits[ ordindex[3] ][0];i<=ysqlimits[ ordindex[3] ][1];i++) for(j=xsqlimits[ ordindex[3] ][0];j<=xsqlimits[ ordindex[3] ][1];j++)  if(dummy[i][j]=='.') game[i][j]='.'; }
   fclose(fp5);
   }
    //cout<<"\nIn loop 3";
   gotoxy(2,22); printf("                                        				       "); gotoxy(2,22);   printf("%g %g %g ",i1,i2,i3);
   endofloop3:
   if(i3==noffilteredpermutations[ordindex[2]]-1) { for(i=ysqlimits[ ordindex[2] ][0];i<=ysqlimits[ ordindex[2] ][1];i++) for(j=xsqlimits[ ordindex[2] ][0];j<=xsqlimits[ ordindex[2] ][1];j++)  if(dummy[i][j]=='.') game[i][j]='.'; }
   fclose(fp4);
   }
    //cout<<"\nIn loop 2";
   gotoxy(2,22); printf("                                        				       "); gotoxy(2,22);   printf("%g %g ",i1,i2);
   endofloop2:
   if(i2==noffilteredpermutations[ordindex[1]]-1) { for(i=ysqlimits[ ordindex[1] ][0];i<=ysqlimits[ ordindex[1] ][1];i++) for(j=xsqlimits[ ordindex[1] ][0];j<=xsqlimits[ ordindex[1] ][1];j++)  if(dummy[i][j]=='.') game[i][j]='.'; }
   fclose(fp3);
   }
    //cout<<"\nIn loop 1";
   gotoxy(2,22); printf("                                        				       "); gotoxy(2,22);   printf("%g ",i1);
   fclose(fp2);
   }
   fclose(fp1);


 ///////////////////////////////////////////////////////////////////////
 end:

 for(i=0;i<9;i++)
  remove(filename[i]);
 //cout<<endl<<endl;

 //display(game);
 //writescreen("screen.txt");
 //cout<<"\n\nFinish";
 //getch();
 //cbab();
 return;
}

//*************************************************************************
// Function check_0 checks consistency of current filled positions while
// check checks for complete solution. Only very slight difference b/w them

int check_0(char game[][9])
{

 int i,j,k,b[9];

 //check rows

 for(i=0;i<9;i++)
  {
  for(k=0;k<9;k++)
  b[k]=0;
  for(j=0;j<9;j++)
   {
    switch (game[i][j])
     {
      case '1':
       b[0]++;
       break;
      case '2':
       b[1]++;
       break;
      case '3':
       b[2]++;
       break;
      case '4':
       b[3]++;
       break;
      case '5':
       b[4]++;
       break;
     case '6':
       b[5]++;
       break;
     case '7':
       b[6]++;
       break;
     case '8':
       b[7]++;
       break;
     case '9':
       b[8]++;
       break;
     default :
       ;
    }
  }
  for( k=0;k<9;k++)
   if(b[k]==2)
    {
     /*cout<<"    -------------------- Row consistency negative.\n";
     display(game);
     writescreen("screen.txt");*/
     return 1;
    }
 }
  //check columns
  for(i=0;i<9;i++)
  b[i]=0;

 for(i=0;i<9;i++)
  {
  for(k=0;k<9;k++)
  b[k]=0;
   for(j=0;j<9;j++)
   {
    switch (game[j][i])
     {
      case '1':
       b[0]++;
       break;
      case '2':
       b[1]++;
       break;
      case '3':
       b[2]++;
       break;
      case '4':
       b[3]++;
       break;
      case '5':
       b[4]++;
       break;
     case '6':
       b[5]++;
       break;
     case '7':
       b[6]++;
       break;
     case '8':
       b[7]++;
       break;
     case '9':
       b[8]++;
       break;
     default :
	 ;
    }
   }
  for(k=0;k<9;k++)
   if(b[k]==2)
    {
     /*cout<<endl;
     cout<<"    -------------------- Column consistency negative. "<<i<<j<<k<<endl;
     display(game);
     writescreen("screen.txt");*/
     return 1;
    }
  }

 return 0;
}
//*************************************************************************
int check(char game[][9])
{

 int i,j,k,b[9];

 //check rows

 for(i=0;i<9;i++)
  {
  for(k=0;k<9;k++)
  b[k]=0;
  for(j=0;j<9;j++)
   {
    switch (game[i][j])
     {
      case '1':
       b[0]++;
       break;
      case '2':
       b[1]++;
       break;
      case '3':
       b[2]++;
       break;
      case '4':
       b[3]++;
       break;
      case '5':
       b[4]++;
       break;
     case '6':
       b[5]++;
       break;
     case '7':
       b[6]++;
       break;
     case '8':
       b[7]++;
       break;
     case '9':
       b[8]++;
       break;
     default :
       ;
    }
  }
  for( k=0;k<9;k++)
   if(b[k]!=1) return 0;
 }
  //check columns
  for(i=0;i<9;i++)
  b[i]=0;

 for(i=0;i<9;i++)
  {
  for(k=0;k<9;k++)
  b[k]=0;
   for(j=0;j<9;j++)
   {
    switch (game[j][i])
     {
      case '1':
       b[0]++;
       break;
      case '2':
       b[1]++;
       break;
      case '3':
       b[2]++;
       break;
      case '4':
       b[3]++;
       break;
      case '5':
       b[4]++;
       break;
     case '6':
       b[5]++;
       break;
     case '7':
       b[6]++;
       break;
     case '8':
       b[7]++;
       break;
     case '9':
       b[8]++;
       break;
     default :
	 ;
    }
   }
  for(k=0;k<9;k++)
   if(b[k]!=1) return 0;
  }

 return 1;
}
/**************************************************************************/
void filterpermutations(char game[][9], char square[][3][3], char square_dum [][3][3])
{
 // the making of possibilities array part copied from slvsudok.cpp
  // -------------- copied part start -------------------------------------
int considered_sq,i,j,k,t,no_of_possibilities,flag_r,flag_c,rowcol[2],r,c,l,p;
char considered_dig,possibilities [9][3][3][9],present[9],missing[9];


initialise_possibilities(possibilities);

for(considered_sq=0;considered_sq<9;considered_sq++)
 {  // main for loop: analyse every square
  t=0; int a=0;         // t=no. of missing digits in square & a=present

 for(i=0;i<3;i++)
  for(j=0;j<3;j++)
   {
    if(square[considered_sq][i][j]>=49&&square[considered_sq][i][j]<=57)
     {
      present[a++]=square[considered_sq][i][j];
     }
    }

   for(i=1;i<=9;i++)
    {
     int found=0;
     for(j=0;j<a;j++)
      {
       if(present[j]==i+48) { found=1; break; }
      }
     if(!found) missing[t++]=i+48;
    }

   //for(i=0;i<t;i++) cout<<missing[i]; //+++++++++++++++++
   //getch(); //+++++++++++++
 for(i=0;i<t;i++)
  {   				// i: analyse every missing digit
   no_of_possibilities=0;
   considered_dig=missing[i];
   //cout<<"\n square : "<<considered_sq<<"  cd:"<<considered_dig;   //+++++++++++++++++
   for(j=0;j<3;j++)
    {    			// j: navigate row
     for(k=0;k<3;k++)
      {  			// k: navigate col
       flag_r=1; flag_c=1;
       if(square_dum[considered_sq][j][k]!='L')
	{ 			// if :check for possibilities where missing
				//     digit can be placed
	 reveal_rc(rowcol,considered_sq,j,k);
	 r=rowcol[0]; c=rowcol[1];
	  //cout<<"\nreveal:"<<r<<" c:"<<c;//++++++++++++++++++++++
	 for(l=0;l<9;l++)
	  {
	   if(game[r][l]==considered_dig) { flag_r=0; }
	   if(game[l][c]==considered_dig) { flag_c=0; }
	  }
	 if(flag_r&&flag_c)
	 {
	  //cout<<" found at:"<<r<<","<<c;//++++++++++++++++++++
	  for(p=0;p<9;p++)
	    {
	     if(possibilities[considered_sq][j][k][p]=='.')
	      {
	       //cout<<" p= "<<p;//+++++++++++++++++++++++
	       break;
	      }
	    }
	    possibilities[considered_sq][j][k][p]=considered_dig;
	     //cout<<" putting "<<possibilities[considered_sq][j][k][p]<<"  at "<<j<<" , "<<k<<" , "<<p;//++++++++++++

	  no_of_possibilities++;
	 }
	}//if finishes
       }//'k' for finishes
      }// 'j' for finishes
   }// 'i' for finishes
 }// 'considered_sq' for finishes

// for(i=0;i<9;i++) for(j=0;j<3;j++) for(k=0;k<3;k++)  for(p=0;p<9;p++) cout<<possibilities[i][j][k][p]; getch(); //++++++++++++++++++++

 //--------------- copied part finish --------------------------------
	 //++++++++++ denotes lines for debugging. better not delete them
 char ch,temppossib[9],string[20];
 FILE *fp,*temp,*log;
  //log=fopen("sudoklog.txt","w"); //+++++++++++++++++

 static char *filename[]=
     {
      "1.txt",
      "2.txt",
      "3.txt",
      "4.txt",
      "5.txt",
      "6.txt",
      "7.txt",
      "8.txt",
      "9.txt"
     };


 for(considered_sq=0;considered_sq<9;considered_sq++)
  {
   int s=0,t2=0,t2t=0;
   //fprintf(log,"\n\nconsidered square %d\n--------------------------\n",considered_sq);   //++++++++++++++++
   for(i=0;i<3;i++)
    {
     for(j=0;j<3;j++,s++)
      {

       t=0;
       for(p=0;p<9 && possibilities[considered_sq][i][j][p]!='.';p++)
	{
	 temppossib[t++]=possibilities[considered_sq][i][j][p];
	}
       if(p!=0)
	{
	 t2++;
	 //fprintf(log,"\n\nCandidate position : %d  possibilities :  ",t2,t2t); //++++++++++++++++++++++++
	 //for(int ii=0;ii<t;ii++)  fprintf(log,"%c,",temppossib[ii]);   //++++++++++++++++++++
	}

       //fprintf(log,"\nt2 : %d     t2t : %d\n",t2,t2t); //+++++++++++++++

       if(t2==t2t+1)
       {
	t2t++;
	fp=fopen(filename[considered_sq],"r");
	temp=fopen("temp.txt","w");
	if(temp==NULL) { cout<<"Temp is Null"; getch(); exit(0); }
	float w=0,i3=1;

	while(!feof(fp))
	 {
	  for(int i2=0;i2<20;i2++) string[i2]='a'; string[19]='\0';
	  fscanf(fp," %[^\n]",string);
	  w++;
	 }

	//fprintf(log,"\ncount = %d\n",w);  //++++++++++++++++
	fclose(fp);
	fp=fopen(filename[considered_sq],"r");

	while(i3<w)
	 {
	  for(int i2=0;i2<20;i2++) string[i2]='a'; string[19]='\0';
	  fscanf(fp," %[^\n]",string);
	  ch=string[2*(t2-1)];
	  //fprintf(log,"\nSquare : %d Position : %d  string : %s \t character %c",considered_sq,t2,string,ch); //++++++++++++++++
	  for(int i1=0;i1<t;i1++)
	   {
	    if(temppossib[i1]==ch)
	      {
	       fprintf(temp,"%s\n",string);
	       //fprintf(log,"\tselecting : %s",string); //+++++++++++++
	      }
	   }
	  i3++;
	 }

	fclose(temp);
	fclose(fp);
	     //	if(t2==3 && considered_sq==2) { fclose(temp); exit(0); }
	remove(filename[considered_sq]);
	rename("temp.txt",filename[considered_sq]);
	//fprintf(log,"\ndone with file : %s",filename[considered_sq]);

       }//if finishes
      }
    }
  }
 //fclose(log);  //+++++++++++++
 return;
}
//*************************************************************************

void interpret(int rc[],char s,char p)
{
 int i,j,r,c,rw[3][3],cl[3][3],rw_[3],cl_[3];

 switch(s)
  {
   case '7':
    rw_[0]=0; rw_[1]=1; rw_[2]=2;
    cl_[0]=0; cl_[1]=1; cl_[2]=2;
    intrp_fill(rw,cl,rw_,cl_);
    break;
   case '8':
    rw_[0]=0; rw_[1]=1; rw_[2]=2;
    cl_[0]=3; cl_[1]=4; cl_[2]=5;
    intrp_fill(rw,cl,rw_,cl_);
    break;
   case '9':
    rw_[0]=0; rw_[1]=1; rw_[2]=2;
    cl_[0]=6; cl_[1]=7; cl_[2]=8;
    intrp_fill(rw,cl,rw_,cl_);
    break;
   case '4':
    rw_[0]=3; rw_[1]=4; rw_[2]=5;
    cl_[0]=0; cl_[1]=1; cl_[2]=2;
    intrp_fill(rw,cl,rw_,cl_);
    break;
   case '5':
    rw_[0]=3; rw_[1]=4; rw_[2]=5;
    cl_[0]=3; cl_[1]=4; cl_[2]=5;
    intrp_fill(rw,cl,rw_,cl_);
    break;
   case '6':
    rw_[0]=3; rw_[1]=4; rw_[2]=5;
    cl_[0]=6; cl_[1]=7; cl_[2]=8;
    intrp_fill(rw,cl,rw_,cl_);
    break;
   case '1':
    rw_[0]=6; rw_[1]=7; rw_[2]=8;
    cl_[0]=0; cl_[1]=1; cl_[2]=2;
    intrp_fill(rw,cl,rw_,cl_);
    break;
   case '2':
    rw_[0]=6; rw_[1]=7; rw_[2]=8;
    cl_[0]=3; cl_[1]=4; cl_[2]=5;
    intrp_fill(rw,cl,rw_,cl_);
    break;
   case '3':
    rw_[0]=6; rw_[1]=7; rw_[2]=8;
    cl_[0]=6; cl_[1]=7; cl_[2]=8;
    intrp_fill(rw,cl,rw_,cl_);
    break;
   default:
    ;
  }//switch finishes

 switch(p)
  {
   case '7':
    r=0; c=0;
    break;
   case '8':
    r=0; c=1;
    break;
   case '9':
    r=0; c=2;
    break;
   case '4':
    r=1; c=0;
    break;
   case '5':
    r=1; c=1;
    break;
   case '6':
    r=1; c=2;
    break;
   case '1':
    r=2; c=0;
    break;
   case '2':
    r=2; c=1;
    break;
   case '3':
    r=2; c=2;
    break;
   default:
    ;
   }//switch finishes

 rc[0]=rw[r][c];
 rc[1]=cl[r][c];
 return;
}
//--------------------------------------------------------------------------
void intrp_fill(int rw[][3],int cl[][3],int rw_[],int cl_[])
{
 int i,j;
  for(i=0;i<3;i++)
   for(j=0;j<3;j++)
    {
     rw[i][j]=rw_[i];
     cl[i][j]=cl_[j];
    }
 return;
}
//--------------------------------------------------------------------------
void reveal_rc(int rwcl[],int consq,int j,int k)
{
 int r,c;
 switch(consq)
  {
   case 0:
    r=j;c=k;
    break;

   case 1:
    r=j;c=k+3;
    break;

   case 2:
    r=j;c=k+6;
    break;

   case 3:
    r=j+3;c=k;
    break;

   case 4:
    r=j+3;c=k+3;
    break;

   case 5:
    r=j+3;c=k+6;
    break;

   case 6:
    r=j+6;c=k;
    break;

   case 7:
    r=j+6;c=k+3;
    break;

   case 8:
    r=j+6;c=k+6;
    break;
   default:
    ;
   }
  rwcl[0]=r;
  rwcl[1]=c;
 return;
}
//--------------------------------------------------------------------------
void mk_squares(char square[][3][3],char game[][9])
{
 int i,j,k,t;

 for(i=0;i<9;i++)
  {
   for(j=0;j<3;j++)
    {
     for(k=0;k<3;k++)
      {
       switch(i)
       {
	case 0:
	 if(j==0) t=0; else if(j==1) t=1; else t=2;
	 square[i][j][k]= game[t][k];
	 break;
	case 1:
	 if(j==0) t=0; else if(j==1) t=1; else t=2;
	 square[i][j][k]= game[t][k+3];
	 break;
	case 2:
	 if(j==0) t=0; else if(j==1) t=1; else t=2;
	 square[i][j][k]= game[t][k+6];
	 break;
	case 3:
	 if(j==0) t=3; else if(j==1) t=4; else t=5;
	 square[i][j][k]= game[t][k];
	 break;
	case 4:
	 if(j==0) t=3; else if(j==1) t=4; else t=5;
	 square[i][j][k]= game[t][k+3];
	 break;
	case 5:
	 if(j==0) t=3; else if(j==1) t=4; else t=5;
	 square[i][j][k]= game[t][k+6];
	 break;
	case 6:
	 if(j==0) t=6; else if(j==1) t=7; else t=8;
	 square[i][j][k]= game[t][k];
	 break;
	case 7:
	 if(j==0) t=6; else if(j==1) t=7; else t=8;
	 square[i][j][k]= game[t][k+3];
	 break;
	case 8:
	 if(j==0) t=6; else if(j==1) t=7; else t=8;
	 square[i][j][k]= game[t][k+6];
	 break;
       }
      }
     }
    }

/*// show squares
 for(i=0;i<9;i++)
    {
     for(j=0;j<3;j++)
      {
       for(k=0;k<3;k++)
       cout<<square[i][j][k];
       cout<<endl;
      }
     cout<<endl;
     getch();
    }
  */
 return;
}
//--------------------------------------------------------------------------

void display(char abc[][9])
{
 int i,j;

 for(i=0;i<9;i++)
  {
   for(j=0;j<9;j++)
    {
     cout<<abc[i][j]<<"  ";
     if( (j+1)%3==0 ) cout<<"  ";
    }
   cout<<endl;
   if((i+1)%3==0) cout<<endl;
  }
  return;
 }
//--------------------------------------------------------------------------

void initialise_possibilities(char posib[][3][3][9])
{
 int i,j,k,l;

 for( i=0;i<9;i++)
 for( j=0;j<3;j++)
 for( k=0;k<3;k++)
 for( l=0;l<9;l++)
 posib[i][j][k][l]='.';

 return;
}
//--------------------------------------------------------------------------
void mk_rand_array(char array[9])

{
  int i,j,t,flag;
 randomize();

 array[0]=48+random(9)+1;

 for(i=1;i<9;i++)
  {

   flag=0;
   t=48+random(9)+1;

   for(j=0;j<i;j++)
    {
     if(t==array[j]) {
		 flag=1;
		 break;
		 }
     else continue ;
     }

    if(flag==0)
	  {
	   array[i]=t;
	  }
    else {
	  i--;
	  }
   }
    /* show array
   for(i=0;i<9;i++)
   cout<<array[i];
   cout<<"\n\n";
   getch();
   */
   return;
 }

//------------------------------------------------------------------------
void mk_board(char board[][9],char array[])
{
  int i,t,k,j;
  for(i=0;i<9;i++)
    {
     t=0;
     k=8-(i-1);
     for(j=0;j<9;j++)
      {
       if(j<i)  board[i][j]=array[k++];
       else     board[i][j]=array[t++];
      }
    }
       /*show board
  for(i=0;i<9;i++)
    {for(j=0;j<9;j++)
     cout<<"   "<<board[i][j];
     cout<<endl;
    }
    getch();*/
    return;
}

//------------------------------------------------------------------------
void rearg_board(char board[][9])
{
   int i,p;
   char swap[9];

    for(i=0;i<9;i++)  swap[i]=board[i][1];
    for(i=0;i<9;i++)  board[i][1]=board[i][3];
    for(i=0;i<9;i++)  board[i][3]=swap[i];


    for(i=0;i<9;i++)  swap[i]=board[i][2];
    for(i=0;i<9;i++)  board[i][2]=board[i][6];
    for(i=0;i<9;i++)  board[i][6]=swap[i];


    for(i=0;i<9;i++)  swap[i]=board[i][5];
    for(i=0;i<9;i++)  board[i][5]=board[i][7];
    for(i=0;i<9;i++)  board[i][7]=swap[i];
    //till yet rearrangements were necessary
    randomize(); // from here onwards rearrangements are not necessary
		 // but are done randomly to ensure random game generation
		 // every time.
    p=random(2);

    switch(p)
     {
      case 0:
       //cout<<"1";
       for(i=0;i<9;i++)  swap[i]=board[i][0];
       for(i=0;i<9;i++)  board[i][0]=board[i][2];
       for(i=0;i<9;i++)  board[i][2]=swap[i];
       break;
      case 1:
       ;
     }

     p=random(2);
     switch(p)
     {
      case 0:
       //cout<<"2";
       for(i=0;i<9;i++)  swap[i]=board[i][3];
       for(i=0;i<9;i++)  board[i][3]=board[i][5];
       for(i=0;i<9;i++)  board[i][5]=swap[i];
       break;
      case 1:
       ;
     }

     p=random(2);
     switch(p)
     {
      case 0:
       //cout<<"3";
       for(i=0;i<9;i++)  swap[i]=board[i][6];
       for(i=0;i<9;i++)  board[i][6]=board[i][8];
       for(i=0;i<9;i++)  board[i][8]=swap[i];
       break;
      case 1:
       ;
     }

    p=random(2);
     switch(p)
     {
      case 0:
       //cout<<"4";
       for(i=0;i<9;i++)  swap[i]=board[6][i];
       for(i=0;i<9;i++)  board[6][i]=board[8][i];
       for(i=0;i<9;i++)  board[8][i]=swap[i];
       break;
      case 1:
       ;
     }

   p=random(2);
     switch(p)
     {
      case 0:
       //cout<<"5";
       for(i=0;i<9;i++)  swap[i]=board[3][i];
       for(i=0;i<9;i++)  board[3][i]=board[5][i];
       for(i=0;i<9;i++)  board[5][i]=swap[i];
       break;
      case 1:
       ;
     }

   p=random(2);
     switch(p)
     {
      case 0:
       //cout<<"6";
       for(i=0;i<9;i++)  swap[i]=board[0][i];
       for(i=0;i<9;i++)  board[0][i]=board[1][i];
       for(i=0;i<9;i++)  board[1][i]=swap[i];
       break;
      case 1:
       ;
     }
	   /*show board
  for(i=0;i<9;i++)
    {for(int j=0;j<9;j++)
     cout<<"   "<<board[i][j];
     cout<<endl;
    }
    getch(); */
    //getch();
    return;
}
//------------------------------------------------------------------------
void squares_to_game(char square[][3][3],char game[][9])
{
 int i,j,k,t;

 for(i=0;i<9;i++)
  {
   for(j=0;j<3;j++)
    {
     for(k=0;k<3;k++)
      {
       switch(i)
       {
	case 0:
	 if(j==0) t=0; else if(j==1) t=1; else t=2;
	 game[t][k]=square[i][j][k];
	 break;
	case 1:
	 if(j==0) t=0; else if(j==1) t=1; else t=2;
	 game[t][k+3]=square[i][j][k];
	 break;
	case 2:
	 if(j==0) t=0; else if(j==1) t=1; else t=2;
	 game[t][k+6]=square[i][j][k];
	 break;
	case 3:
	 if(j==0) t=3; else if(j==1) t=4; else t=5;
	 game[t][k]=square[i][j][k];
	 break;
	case 4:
	 if(j==0) t=3; else if(j==1) t=4; else t=5;
	 game[t][k+3]=square[i][j][k];
	 break;
	case 5:
	 if(j==0) t=3; else if(j==1) t=4; else t=5;
	 game[t][k+6]=square[i][j][k];
	 break;
	case 6:
	 if(j==0) t=6; else if(j==1) t=7; else t=8;
	 game[t][k]=square[i][j][k];
	 break;
	case 7:
	 if(j==0) t=6; else if(j==1) t=7; else t=8;
	 game[t][k+3]=square[i][j][k];
	 break;
	case 8:
	 if(j==0) t=6; else if(j==1) t=7; else t=8;
	 game[t][k+6]=square[i][j][k];
	 break;
       }
      }
     }
    }

 return;
}

//-------------------------------------------------------------------------
/**************************************************************************/
//========= NO. OF 'ON' POSITIONS CAN BE CONTROLLED =======================
//================= USING THIS FUNCTION :- ==================================
/**************************************************************************/
void mk_solvable_game(char game[][9])
{

  int rand_r[34],rand_c[34];
  static int n=0;
  char formed_incomplete_game_for_checking[9][9],
       formed_incomplete_game_for_playing[9][9];
       // the "formed_incomplete_game_for_playing" array is needed 'coz
       // solvable function checks the solvability of "formed_incomplete_game_for_checking"
       // by actually solving it and if it is solved,it("question") will be
       // lost!

  randomize();    // note: although an array of 34 has been declared
		  // but actual 'on' positions may be less 'coz randomly
		  // two same pair may get generated
  again:
  n++;

  //cout<<"Please Wait while the puzzle is being generated..\n\nOut of randomly generated puzzlez, only a logically solvable puzzle will \nbe given.";
  clrscr();

  cout<<"Please wait while a Logically solvable puzzle is generated out of random puzzles\n\nAnalysing random puzzle number : "<<n<<"\n";
  for( int i=0;i<9;i++)
    for(int j=0;j<9;j++)
      formed_incomplete_game_for_checking[i][j]='.';

  for(i=0;i<34;i++)
   {
    int a=random(9);
    int b=random(9);
    rand_r[i]=a;
    rand_c[i]=b;
   }

  for( i=0;i<34;i++)
   formed_incomplete_game_for_checking [rand_r[i]][rand_c[i]]
				  =game[rand_r[i]][rand_c[i]];

  for(i=0;i<9;i++)
  for(j=0;j<9;j++)
  formed_incomplete_game_for_playing[i][j] =
  formed_incomplete_game_for_checking[i][j];

  //display(game);
  //cout<<endl<<"In mk_solvable_game...\n";
  //display(formed_incomplete_game_for_checking);
  //getch();
  if(solvable(formed_incomplete_game_for_checking))
   {
    //display(formed_incomplete_game_for_playing);
    for(i=0;i<9;i++)
    for(j=0;j<9;j++)
     {
      game[i][j]=formed_incomplete_game_for_playing[i][j];
     }
   }
  else goto again;
  return;

 }
 //------------------------------------------------------------------------
  ////////// This is basically copy paste of case '2' in main program ///////
  //// Only here there is no output if game is solved. Instead success is ///
  // sent to the calling function. Also the terminating condition is different//

 int solvable(char game[][9])
{
 char dummy[9][9],missing[9],present[9],
      possibilities[9][3][3][9],square[9][3][3],square_dum[9][3][3];
 char d,sq,pos,considered_dig;
 int i,j,k,t,l,m,p,q,r,c,rowcol[2],considered_sq,flag_r,flag_c,
     no_of_possibilities,notsolved ;

 /****************** initialization **********************/
 for( i=0;i<9;i++)
 for( j=0;j<9;j++)
 { dummy[i][j]='.'; }

 initialise_possibilities(possibilities);

 /****************** make dummy ***************************/
 for(i=0;i<9;i++)
  for(j=0;j<9;j++)
   {
    if(isdigit(game[i][j]))
     {
      dummy[i][j]='L';
     }
    else;
   }
 /////////////////////////////////////////////////////////////////
 mk_squares(square,game);
 mk_squares(square_dum,dummy);
 //************************* solution ********************************
 q=0;
 do{

for(considered_sq=0;considered_sq<9;considered_sq++)
 {  // main for loop: analyse every square
  t=0; int a=0;         // t=no. of missing digits in square & a=present
  initialise_possibilities(possibilities);

 for(i=0;i<3;i++)
  for(j=0;j<3;j++)
   {
    if(square[considered_sq][i][j]>=49&&square[considered_sq][i][j]<=57)
     {
      present[a++]=square[considered_sq][i][j];
     }
    }

   for(i=1;i<=9;i++)
    {
     int found=0;
     for(j=0;j<a;j++)
      {
       if(present[j]==i+48) { found=1; break; }
      }
     if(!found) missing[t++]=i+48;
    }

   //for(i=0;i<t;i++) cout<<missing[i]; //+++++++++++++++++
   //getch(); //+++++++++++++
 for(i=0;i<t;i++)
  {   				// i: analyse every missimg digit
   no_of_possibilities=0;
   considered_dig=missing[i];
   //cout<<"\n square : "<<considered_sq<<"  cd:"<<considered_dig;   //+++++++++++++++++
   for(j=0;j<3;j++)
    {    			// j: navigate row
     for(k=0;k<3;k++)
      {  			// k: navigate col
       flag_r=1; flag_c=1;
       if(square_dum[considered_sq][j][k]!='L')
	{ 			// if :check for possibilities where missing
				//     digit can be placed
	 reveal_rc(rowcol,considered_sq,j,k);
	 r=rowcol[0]; c=rowcol[1];
	  //cout<<"\nr:"<<r<<" c:"<<c;//++++++++++++++++++++++
	 for(l=0;l<9;l++)
	  {
	   if(game[r][l]==considered_dig) { flag_r=0; }
	   if(game[l][c]==considered_dig) { flag_c=0; }
	  }
	 if(flag_r&&flag_c)
	 {
	  //cout<<" found at:"<<r<<","<<c;//++++++++++++++++++++
	  for(p=0;p<9;p++)
	    {
	     if(possibilities[considered_sq][j][k][p]=='.')
	      {
	       //cout<<" p= "<<p;//+++++++++++++++++++++++
	       break;
	      }
	    }
	    possibilities[considered_sq][j][k][p]=considered_dig;
	     //cout<<" putting "<<possibilities[considered_sq][j][k][p]
	       //	<<"  at "<<j<<" , "<<k<<" , "<<p;//++++++++++++

	  no_of_possibilities++;
	 }
	}//if finishes
       }//'k' for finishes
      }// 'j' for finishes

 //along with current,analyse keep checking if some locked digits can be found:-
     //part 1: for those digits which have only one possible place
     //cout<<"  nop :"<<no_of_possibilities; //++++++++++
     //getch();  //++++++++++++
     //clrscr(); //++++++++++++
     //display(game);//+++++++++++++
     if(no_of_possibilities==1)
      {
       for(j=0;j<3;j++)
	{    			// j: navigate row
	 for(k=0;k<3;k++)
	  {    			// k: navigate col
	   for(l=0;l<9;l++)     // l: navigate available possibilities
	    {
	     if(possibilities[considered_sq][j][k][l]==considered_dig)
	      {
	       //cout<<"================== part 1 ===============";//++++++++++
	       reveal_rc(rowcol,considered_sq,j,k);
	       r=rowcol[0]; c=rowcol[1];
	       //cout<<"\nputting at : "<<r<<" , "<<c<<" j,k are"<<j<<","<<k; //+++++++++
	       game[r][c]=considered_dig;
	       dummy[r][c]='L';
	       mk_squares(square,game);
	       mk_squares(square_dum,dummy);
	       goto part1_done;
	      }
	   } // 'l' for finishes
	  } // 'k' for finishes
	}  // 'j' for finishes
      }   // if finishes
      part1_done:
    }//  'i' for finishes

   //part 2:after analysis of whole square, check it again for those unlocked
   //       positions which have only one missing digit as possible digit.
  int s=0,s2;
   for(j=0;j<3;j++)
    {    			// j: navigate row
     for(k=0;k<3;k++)
      {                         // k : navigate col
       if(square_dum[considered_sq][j][k]!='L')
	{
	 for(l=0;l<9;l++)     // s: to count no. of possible digits
	  {
	   if(possibilities[considered_sq][j][k][l]>=49 &&
	      possibilities[considered_sq][j][k][l]<=57)
	   { s++; s2=l; }
	  }   // 'l' for finishes
	if(s==1)
	 {
	  int only_possible_here=possibilities[considered_sq][j][k][s2];
	  reveal_rc(rowcol,considered_sq,j,k);
	  r=rowcol[0]; c=rowcol[1];
	  //cout<<"================== part 2 ===============";//++++++++++
	  game[r][c]=only_possible_here;
	  dummy[r][c]='L';
	  mk_squares(square,game);
	  mk_squares(square_dum,dummy);
	 } //'s' if finishes
	} // if finishes
      } //'k' for finishes
    }  // 'j' for finishes
 } //main for loop finishes

 int temp=0;

 for(i=0;i<9;i++)
 for(j=0;j<9;j++)
  {
   if(dummy[i][j]!='L')
      {
       notsolved=1; q++;
       if(q==100) // IT BEING 'ASSUMED' THAT A GAME NOT SOLVED IN 100 ROUNDS
		  // CANNOT BE SOLVED
       {
	return 0;
       }
       goto see_if_next_is_reqd;
      }
       else temp++;
   }

 if(temp==81) notsolved=0;

 see_if_next_is_reqd:
 }while(notsolved);
 ///////////////////////////////////////////////////////////////////////
 return 1;
}
//-------------------------------------------------------------------------

void mk_dummy(char g[][9],char d[][9])
{
 for(int i=0;i<9;i++)
  for(int j=0;j<9;j++)
   {
    if(isdigit(g[i][j]))
     d[i][j]='L';
    else d[i][j]='.';
   }
  return;
 }
//--------------------------------------------------------------------------
void display_col(char abc[][9],char xyz[][9])
{
  int i,j;         //abc=game   xyz=dummy_g

 for(i=0;i<9;i++)
  {
   for(j=0;j<9;j++)
    {
     if(xyz[i][j]=='L')
       textcolor(LIGHTRED);
     else
      {
       if(isdigit(abc[i][j]) )
       textcolor(LIGHTGREEN);
       else textcolor(WHITE);
      }
      putch(abc[i][j]); cout<<"  ";
      if( (j+1)%3==0 ) cout<<"  ";
    }
   cout<<endl;
   if((i+1)%3==0) cout<<endl;
  }
 textcolor(WHITE);
  return;
 }
//---------------------------------------------------------------------
void make_ordindex(int ord[], float nofp[])
{

 float tempf[9],z,zi;
 int i,j,t,nofp_d[9],tempindx[9];

 for(i=0;i<9;i++) {nofp_d[i]=1;}

 for(i=0;i<9;i++)
  {
   t=0;
   for(j=0;j<9;j++)
    {
     if(nofp_d[j]==1) { tempf[t++]=nofp[j]; tempindx[t-1]=j; }
    }

   //for(j=0;j<t;j++) {   cout<<" "<<tempindx[j];  }
   //cout<<endl;

   z=tempf[0];  zi=tempindx[0];
   for(j=0;j<t;j++)
    {
     if(tempf[j]<=z) { z=tempf[j]; zi=tempindx[j]; }
    }
   ord[i]=zi;
   nofp_d[zi]=0;
  }

 return;
}

//--------------------------------------------------------------------------
void show_message()
{
  clrscr();
  cout<<"		About Game\n";
  hline();
  cout<<endl<<endl;
  cout<<"Sudoku involves filling the empty positions in the board with digits\n"
      <<"  from 1 to 9 in such a way that:\n\n\n"
      <<" 1) Every row contains every digit ( ie. all 1 to 9)\n"
      <<" 2) Every column contains every digit (ie. all 1 to 9)\n"
      <<" 3) Every 3 X 3 'Square' contains every digit (ie. all 1 to 9 )\n\n\n"
      <<"\n\n\n\nPRESS ANY KEY TO CONTINUE...";
   getch();

  clrscr();
  cout<<"		About Software\n";
  hline();
  cout<<endl<<endl;

  cout<<" This software :\n\n\n"
      <<" 	1. Generates only LOGICALLY SOLVABLE puzzles which don't require any\n"
      <<"           GUESS WORK.\n\n"
      <<"	2. Generates a RANDOM PUZZLE everytime, So a puzzle practically never\n"
      <<"           repeats itself.\n\n"
      <<"   	3. The Puzzle solver can solve ANY SUDOKU (with even 1 clue given).\n\n"
      <<"	4. The Puzzle solver gives ALTERNATE SOLUTIONS too if they exist."
      <<"\n\n\n\nPRESS ANY KEY TO CONTINUE...";
   getch();

  clrscr();
  cout<<"	         How to enter digits ( overview )\n";
  hline();
  cout<<endl<<endl;
  cout<<"The empty positions in the board will be shown by dots.\n\n\n\n"
      <<"To enter a digit, you need to press just ONE KEY for each of following steps:-\n\n\n\n\n"
      <<"STEP 1: Select the 3 X 3 'Square' containing desired Position\n"
      <<"STEP 2: Select the desired Position in the Selected Square\n"
      <<"STEP 3: Enter the digit desired to be placed at the selected position\n\n\n"
      <<" PRESS ANY KEY TO CONTINUE...";
   getch();

  clrscr();
  cout<<"	         How to select square and position\n";
  hline();
  cout<<endl<<endl;
  cout<<"USE THE NUMERIC KEYPAD\n\n"
      <<"Press a key from 1 to 9 whose 'Relative position' in the keypad\n"
      <<"is same as that of desired square in the board. eg.\n\n"
      <<"	Press 7 : To select topmost-leftmost square\n"
      <<"	Press 9 : To select topmost-rightmost square\n"
      <<"	Press 1 : To select bottommost-leftmost square\n"
      <<"	Press 5 : To select middlemost square  etc.\n\n\n"
      <<"After selecting square, procedure to select the position in that\n"
      <<"square is same as described above\n\n\n"
      <<" PRESS ANY KEY TO CONTINUE...";

   getch();

  clrscr();
  cout<<"	         continued...\n";
  hline();
  cout<<endl<<endl;
  cout<<"To ERSASE or change a digit :\n\n"
      <<" Chose the position to edit as described earlier.\n\n\n\n"
      <<" Enter new digit you want to place....or\n\n"
      <<" Entering dot (fullstop) will erase that digit\n\n";
  hline();
  cout<<"\nEnter 0 (zero) as square,position, and digit to submit the puzzle\n"
      <<"      e as square,position, or digit to exit game anywhere\n\n\n"
      <<" PRESS ANY KEY TO CONTINUE...";
    getch();
  clrscr();
  cout<<" NOTE:\n\n"
      <<"  Since out of ramdomly generated puzzles it asks only logically solvable\n"
      <<"  puzzles, so the puzzle generation may take some time.\n\n"
      <<"  While giving computer a puzzle to solve, do not enter an INVALID SUDOKU i.e.\n"
      <<"  which by ITSELF is inconsistent. (Then the program may end abruptly)\n\n"
      <<"  Give it only a VALID SUDOKU i.e. which is consistent with the rules of sudoku.\n\n\n\n"
      <<"  Screen can be maximised and minimised by pressing alt + <enter>";
   getch();
   clrscr();
  return;
 }
