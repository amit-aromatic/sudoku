#include<conio.h>
#include<iostream.h>
#include<stdio.h>


#define MAX1 100

unsigned long fact(unsigned long);
unsigned long sigma_fact_1_to(unsigned long);

void fpermut(char a[],char name[],int n)
{
 char t[MAX1],t2,t3[MAX1][MAX1];
 unsigned long i,j,k,l,m,p;
 FILE *fp,*fp2;

 /*
 clrscr();

 n=5;


 for(i=0;i<n;i++)
  a[i]=i+97;
  */
 if(n>0)
 {
  fp=fopen(name,"w");
  fprintf(fp,"%c ",a[0]);
  fclose(fp);
 }

 for(i=0;(i<n-1) && (!(n<=0)) ;i++)
  {
    //NOTE THE IMPORTANCE OF THE TERMINATION CONDITION OF THIS FOR LOOP
    //SINCE I=UNSIGNED IT DOES NOT STOP IF N<=0
   fp=fopen(name,"r");
   fp2=fopen("temp.rtf","w");

      t2=a[i+1];

    for(j=0;j<fact(i+1);j++)
     {
      for(l=0;l<(i+1);l++)
       {
	fscanf(fp," %c",&t[l]);
       }
	 fscanf(fp,"\n");

      for(p=0;p<(i+2);p++)
       {
	for(l=0,m=0;m<(i+2);)
	 {
	    if(p==m)
	     t3[p][m++]=t2;
	    else t3[p][m++]=t[l++];
	 }
       }

      for(p=0;p<(i+2);p++)
       {
	for(m=0;m<(i+2);m++)
	 fprintf(fp2,"%c ",t3[p][m]);
	fprintf(fp2,"\n");
       }
     }
   fclose(fp);
   fclose(fp2);
   remove(name);
   rename("temp.rtf",name);
   //clrscr();
   //printf("Please Wait...");
   }

//clrscr();

//cout<<"finish\nSee file \"Permut.rtf\" for output.";
//getch();
}

unsigned long fact(unsigned long n)
 {
  unsigned long i,p=1;

  if(n==0) return 0;        // false mathematically modified foe slvsudk2.cpp

  else
   {
    for(i=1;i<=n;i++)
    p*=i;
    return p;
   }
 }

unsigned long sigma_fact_1_to(unsigned long n)
 {
  unsigned long i,p=0;

  for(i=1;i<=n;i++)
   p+=fact(i);

  return p;
 }
