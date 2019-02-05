//15816032 Œã“¡ŠC“l
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXLENGTH 10

char buf[MAXLENGTH];

int remaincounting(int **open,int rows,int columns);
int markcounting(int **mark,int rows,int columns);
void printdata(int **data,int **open,int **mark,int Game,int rows,int columns);
void zerobomb(int **data,int **open,int **mark,int x,int y,int rows,int columns);
void openingcell(int **data,int **open,int **mark,int *x,int *y,int rows,int columns);
void markingcell(int **data,int **open,int **mark,int *x,int *y,int rows,int columns);
void removingmark(int **data,int **open,int **mark,int *x,int *y,int rows,int columns);

int remaincounting(int **open,int rows,int columns){
  int i,j,count=0;
  for(i=1;i<rows-1;i++){
    for(j=1;j<columns-1;j++){
      if(!open[i][j]) count++;
    }
  }
  return count;
}
int markcounting(int **mark,int rows,int columns){
  int i,j,count=0;
  for(i=1;i<rows-1;i++){
    for(j=1;j<columns-1;j++){
      if(mark[i][j]) count++;
    }
  }
  return count;
}

void printdata(int **data,int **open,int **mark,int Game,int rows,int columns){
	int i,j;
	printf("  ");
	for(j=1;j<columns-1;j++){
		printf("| %2d",j-1);
	}
	printf("\n--+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---\n");
	for(i=1;i<rows-1;i++){
		printf("%2d",i-1);
		for(j=1;j<columns-1;j++){
			if(Game == 0){
				if(*(open[i]+j)==0&&mark[i][j]==0)
					printf("| ? ");
				else if(mark[i][j]==1)
					printf("| M ");
				else
					printf("| %d ",*(data[i]+j));
			}
			else{
				if(*(data[i]+j)!=-1)
					printf("| %d ",*(data[i]+j));
				else
					printf("| X ");
			}
		}
		printf("\n");
	}
	if(Game == 1)
		printf("GAME OVER!\n");
}


void zerobomb(int **data,int **open,int **mark,int x,int y,int rows,int columns){
  if(1<=x&&x<=rows-2&&1<=y&&y<=columns-2){
    if(*(open[x-1]+y-1)==0&&*(mark[x-1]+y-1)==0){*(open[x-1]+y-1)=1; if(*(data[x-1]+y-1)==0) zerobomb(data,open,mark,x-1,y-1,rows,columns);}
    if(*(open[x-1]+y)==0&&*(mark[x-1]+y)==0){*(open[x-1]+y)=1;   if(*(data[x-1]+y)==0) zerobomb(data,open,mark,x-1,y,rows,columns);}
    if(*(open[x-1]+y+1)==0&&*(mark[x-1]+y+1)==0){*(open[x-1]+y+1)=1; if(*(data[x-1]+y+1)==0) zerobomb(data,open,mark,x-1,y+1,rows,columns);}
    if(*(open[x]+y-1)==0&&*(mark[x]+y-1)==0){*(open[x]+y-1)=1;   if(*(data[x]+y-1)==0) zerobomb(data,open,mark,x,y-1,rows,columns);}
    if(*(open[x]+y+1)==0&&*(mark[x]+y+1)==0){*(open[x]+y+1)=1;   if(*(data[x]+y+1)==0) zerobomb(data,open,mark,x,y+1,rows,columns);}
    if(*(open[x+1]+y-1)==0&&*(mark[x+1]+y-1)==0){*(open[x+1]+y-1)=1; if(*(data[x+1]+y-1)==0) zerobomb(data,open,mark,x+1,y-1,rows,columns);}
    if(*(open[x+1]+y)==0&&*(mark[x+1]+y)==0){*(open[x+1]+y)=1;   if(*(data[x+1]+y)==0) zerobomb(data,open,mark,x+1,y,rows,columns);}
    if(*(open[x+1]+y+1)==0&&*(mark[x+1]+y+1)==0){*(open[x+1]+y+1)=1; if(*(data[x+1]+y+1)==0) zerobomb(data,open,mark,x+1,y+1,rows,columns);}
	}
}
void openingcell(int **data,int **open,int **mark,int *x,int *y,int rows,int columns){
	int n,del;
	while(1){
			printf("Enter the coordinate of a cell to open\n");
			printf("(row and column numbers divided by an en space):");
			fgets(buf,sizeof(buf),stdin);
			n = sscanf(buf,"%d %d %d",x,y,&del);
			*x = *x+1; *y = *y+1;
			if(1>*x||*x>rows-1||1>*y||*y>columns-1||n != 2){
				printf("Incorrect coordinate!\n");
				printdata(data,open,mark,0,rows,columns);
			}
			else if(*(open[*x]+(*y))!=0){
				printf("The cell is already open.\n");
				printdata(data,open,mark,0,rows,columns);
			}
			else if(*(mark[*x]+(*y))!=0){
				printf("To open the cell, remove its marking first.\n");
				printdata(data,open,mark,0,rows,columns);	
			}
			else{
				*(open[*x]+(*y))=1;
				break;
			}
		}
}
void markingcell(int **data,int **open,int **mark,int *x,int *y,int rows,int columns){
	int n,del;
	while(1){
			printf("Enter the coordinate of a cell to mark\n");
			printf("(row and column numbers divided by an en space):");
			fgets(buf,sizeof(buf),stdin);
			n = sscanf(buf,"%d %d %d",x,y,&del);
			*x = *x+1; *y = *y+1;
			if(1>*x||*x>rows-1||1>*y||*y>columns-1||n != 2){
				printf("Incorrect coordinate!\n");
				printdata(data,open,mark,0,rows,columns);
			}
			else if(*(mark[*x]+(*y))!=0){
				printf("The cell is already marked.\n");
				printdata(data,open,mark,0,rows,columns);
			}
			else if(*(open[*x]+(*y))!=0){
				printf("The cell is already open.\n");
				printdata(data,open,mark,0,rows,columns);
			}
			else{
				*(mark[*x]+(*y))=1;
				break;
			}
		}
}

void removingmark(int **data,int **open,int **mark,int *x,int *y,int rows,int columns){
  int n,del;
	while(1){
			printf("Enter the coordinate of a cell to remove marking\n");
			printf("(row and column numbers divided by an en space):");
			fgets(buf,sizeof(buf),stdin);
			n = sscanf(buf,"%d %d %d",x,y,&del);
			*x = *x+1; *y = *y+1;
			if(1>*x||*x>rows-1||1>*y||*y>columns-1||n != 2){
				printf("Incorrect coordinate!\n");
				printdata(data,open,mark,0,rows,columns);
			}
			else if(*(mark[*x]+(*y))==0){
        printf("The cell is not marked.\n");
				printdata(data,open,mark,0,rows,columns);
			}
			else if(*(open[*x]+(*y))!=0){
				printf("The cell is already open.\n");
				printdata(data,open,mark,0,rows,columns);
			}
			else if(*(mark[*x]+(*y))!=0){
        *(mark[*x]+(*y))=0;
				break;
			}
			
		}
}


int main(){
	int **data,**open,**mark,i,j,bom,count=0,remaincount,markcount,x=0,y=0,rows,columns,degree,choice;

	srand(time(NULL));
	while(1){
		printf("Enter the number of rows (an integer within the range from 5 to 15):");
		fgets(buf,sizeof(buf),stdin);
    sscanf(buf,"%d",&rows);
		if(rows<5||15<rows){
			printf("Invalid Value! Enter an integer within the range from 5 to 15.\n");
		}
		else{
			break;
		}
	}
	while(1){
		printf("Enter the number of columns (an integer within the range from 5 to 15):");
		fgets(buf,sizeof(buf),stdin);
		sscanf(buf,"%d",&columns);
		if(columns<5||15<columns){
			printf("Invalid Value! Enter an integer within the range from 5 to 15.\n");
		}
		else{
			break;
		}
	}
	while(1){
		printf("Select the degree of difficulty of the game (1: novice, 2: middle, 3: advanced):\n");
		fgets(buf,sizeof(buf),stdin);
		sscanf(buf,"%d",&degree);
		if(1<=degree&&degree<=3){
			break;
		}
		printf("Invalid Value! Enter either 1,2, or 3.\n");
	}
	rows = rows+2;
	columns = columns+2; 
	data = (int **)calloc(rows,sizeof(int*));
	open = (int **)calloc(rows,sizeof(int*));
	mark = (int **)calloc(rows,sizeof(int*));
	for(i=0;i<rows;i++){
		data[i]=(int *)calloc(columns,sizeof(int*));
		open[i]=(int *)calloc(columns,sizeof(int*));
		mark[i]=(int *)calloc(columns,sizeof(int*));
	}


	for(i=1;i<rows-1;i++){
		for(j=1;j<columns-1;j++){
			bom=rand()%10+1;
			if(bom<=degree){
				data[i][j]=-1;
				count++;
			}
		}
	}
	for(i=1;i<rows-1;i++){
		for(j=1;j<columns-1;j++){
			if(data[i][j]==-1){
				if(data[i-1][j-1]!=-1)data[i-1][j-1]++;
				if(data[i-1][j]!=-1)data[i-1][j]++;
				if(data[i-1][j+1]!=-1)data[i-1][j+1]++;
				if(data[i][j-1]!=-1)data[i][j-1]++;
				if(data[i][j+1]!=-1)data[i][j+1]++;
				if(data[i+1][j-1]!=-1)data[i+1][j-1]++;
				if(data[i+1][j]!=-1)data[i+1][j]++;
				if(data[i+1][j+1]!=-1)data[i+1][j+1]++;

			}
			
		}
	}
	
	printdata(data,open,mark,0,rows,columns);
	printf("The number of mined cells: %d\n",count);
	remaincount = rows*columns - count;
	while(1){
    markcount = markcounting(mark,rows,columns);
    if(remaincount==markcount-count){
      removingmark(data,open,mark,&x,&y,rows,columns);
      choice = 0;
    }
		else if(markcount == 0){
			while(1){
        printf("Select the operation ");
				printf("(1: open, 2: mark): ");
				fgets(buf,sizeof(buf),stdin);
				sscanf(buf,"%d",&choice);
				if(choice==1||choice==2){
					break;
				}
				printf("Invalid Value!\n");
				
			}

		}
		else if(markcount != 0){
			while(1){
        printf("Select the operation ");
				printf("(1: open, 2: mark, 3: remove marking): ");
				fgets(buf,sizeof(buf),stdin);
				sscanf(buf,"%d",&choice);
				if(choice==1||choice==2||choice==3){
					break;
				}
				printf("Invalid Value!\n");
			}

		}
		if(choice==1)
			openingcell(data,open,mark,&x,&y,rows,columns);
		if(choice==2)
			markingcell(data,open,mark,&x,&y,rows,columns);
		if(choice==3)
			removingmark(data,open,mark,&x,&y,rows,columns);
		
		if(data[x][y]==-1 &&open[x][y]==1){
			printdata(data,open,mark,1,rows,columns);
			free(data);
			free(open);
			return 0;
		}
		else if(data[x][y]==0 && open[x][y]==1){
		  zerobomb(data,open,mark,x,y,rows,columns);
		  
		}
		remaincount = remaincounting(open,rows,columns)-count;
		if(remaincount==0){
			printdata(data,open,mark,2,rows,columns);
			printf("Congratulations!\n");
			free(data);
			free(open);
			return 0;
		}
		else
      printdata(data,open,mark,0,rows,columns);
		
		printf("The number of remaining cells to open: %d\n",remaincount);
		

	}
	free(data);
	free(open);

	return 0;
}