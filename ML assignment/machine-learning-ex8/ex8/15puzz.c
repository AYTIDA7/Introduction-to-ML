#include <stdio.h>
#define UP	  0
#define DOWN  1
#define LEFT  2
#define RIGHT 3


typedef struct node{
	int mat[4][4];
	int h;
	struct node * parent;
}matrix;

typedef struct nd{
	matrix * m;
	struct nd * next;
}pq;



typedef struct z{
	int i;
	int j;
}zeroIndex;

void add(pq *Q,matrix *m)
{
	pq *temp = (pq*)malloc(sizeof(pq)),*q=Q;
	temp->m = m;
	if(q==NULL)
	{
		q=temp;
	}
	else
	{
		while(q!=NULL)
		{
			if(q->next->m->h >= m->h)
			{
				temp->next = q->next;
				q->next = temp;
				break;
			}
			q=q->next;
		}
	}
	
}
void pop(pq *q)
{
	pq *temp = q;
	q=q->next;	
	free(temp);
}
int checkInClosed(matrix *m)
{
	
}
//------------------------------------------------------------------------------

matrix *assignVals(int a[][4])
{
	matrix *t = (matrix*)malloc(sizeof(matrix)); 
	int i,j;
	for(i = 0 ; i < 4; i++)
	{
		for(j = 0 ; j < 4 ; j++)
		{
			t->mat[i][j] = a[i][j];
		}
	}
	t->h = 0;
	t->parent = NULL;
	return t;
}
void calh(matrix *m)
{
	int i,j;
	m->h = 0;
	for(i = 0 ; i < 4 ; i++)
	{
		for(j = 0 ; j<4 ; j++)
		{
			if(m->mat[i][j] != 4i + j + 1 && m->mat[i][j] == 0)
			{
				m->h++;
			}
		}
	}	
}
int isGoalstate(matrix *m)
{
	int i,j;
	for(i = 0 ; i < 4 ; i++)
	{
		for(j = 0 ; j<4 ; j++)
		{
			if(m->mat[i][j] != 4i+1 && m->mat[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
zeroIndex getZero(matrix *m)
{
	zeroIndex z;
	for(i = 0 ; i < 4 ; i++)
	{
		for(j = 0 ; j<4 ; j++)
		{
			if(m->mat[i][j] == 0)
			{
				z.i = i;
				z.j = j;
			}
		}
	}

	return z;
}
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
matrix * findNextState(matrix *M, zeroIndex z, int state)
{
	matrix *m = assignVals(M->mat);
	switch(state)
	{
		case state == UP 	: 	swap(m->mat[z.i][z.j],m->mat[z.i-1][z.j]);
								break;
		case state == DOWN 	: 	swap(m->mat[z.i][z.j],m->mat[z.i+1][z.j]);
								break;
		case state == LEFT 	: 	swap(m->mat[z.i][z.j],m->mat[z.i][z.j-1]);
								break;
		case state == RIGHT : 	swap(m->mat[z.i][z.j],m->mat[z.i][z.j+1]);
								break;

	}
	calh(m);
	return m;
}
void getNewStates(matrix *m)
{
	zeroIndex z= zeroIndex.getZero(m);
	if(z.i > 0)
	{
		matrix *M = findNextState(m->a,z,UP);
		if(isGoalstate(M))
		{
			printSuccess(M);
			return;
		}
		openState.add(M);
	}
	if(z.i < 3)
	{
		matrix *M = findNextState(m->a,z,DOWN);
		if(isGoalstate(M))
		{
			printSuccess(M);
			return;
		}
		openState.add(M);
	}
	if(z.j > 0)
	{
		matrix *M = findNextState(m->a,z,LEFT);
		if(isGoalstate(M))
		{
			printSuccess(M);
			return;
		}
		openState.add(M);
	}
	if(z.j > 3)
	{
		matrix *M = findNextState(m->a,z,RIGHT);
		if(isGoalstate(M))
		{
			printSuccess(M);
			return;
		}
		openState.add(M);
	}
}