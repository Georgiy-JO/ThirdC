#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <conio.h>

typedef struct node {
	int val;
	int amo;
	struct node* l, * r;
} tree;

void simplemix(int* a, int n, int del)
{	
	srand(time(NULL));
	for (int i = 0, num1, num2, temp; i < n;i++)
	{
		num1 = rand() * n / RAND_MAX-1;
		if (num1 < 0)
			num1 = -num1;
		num2= rand() * n / RAND_MAX-1;
		if (num2 < 0)
			num2 = -num2;
		temp = a[num1];
		a[num1] = a[num2];
		a[num2] = temp;
	}
	/*
	int temp;
	if (del != 1 && del < n)
	{
		for (int i = 0; i < n / 2; i++)
		{
			if (i % del == 0)
			{
				temp = a[n - i - 1];
				a[n - i - 1] = a[i];
				a[i] = temp;
			}
		}
		del--;
		simplemix(a, n, del);
	}
	*/
}
/*
tree* createtree(tree* a)
{
	tree* tmp = (tree*)malloc(sizeof(tree));
	tmp->l = NULL;
	tmp->r = NULL;
	tmp->amo = 0;
	tmp->val = 0;
	return tmp;

}
*/
tree* addison(tree* a, int b)
{
	if (a == NULL)
	{
		tree* temp = (tree*)malloc(sizeof(tree));
		temp->l = NULL;
		temp->r = NULL;
		temp->val = b;
		temp->amo=1;
		return temp;
	}
	else
	{
		if (a->val == b)
		{
			a->amo++;
		}
		else
		{
			if (b < a->val)
			{
				a->l = addison(a->l, b);
			}
			else
			{
				a->r = addison(a->r, b);
			}
		}
		return a;
	}
}
void printMe(tree* wood, int* f, int* i)
{
	if (wood == NULL)
		return 0;
	else
	{
		printMe(wood->l, f, i);
		for (int j = 0; j < wood->amo; j++)
		{
			f[(*i)] = wood->val;
			(*i)++;
		}
		printMe(wood->r, f, i);
	}
}


int main()
{

	FILE* f1 = fopen("input.bin", "rb");
	FILE* f2 = fopen("output.bin", "wb");
	int n = 0, tempp;
	fread(&n, sizeof(int), 1, f1);
	if (n != 0)
	{
		int* a = (int*)calloc(n, sizeof(int));
		fread(a, sizeof(int), n, f1);
		//simplemix(a, n, 6);
		srand(time(NULL));
		for (int i = 1, j; i < n; i++)
		{
			tempp = rand();
			if (tempp < 0)
				tempp *= -1;
			tempp = tempp % i;
			j = a[tempp];
			a[tempp] = a[i];
			a[i] = j;
		}
		tree* b = (tree*)calloc(1, sizeof(tree));
		tree* root = b;
		b->r = NULL;
		b->amo = 1;
		b->l = NULL;
		//fread(&b->val, sizeof(int), 1, f1);
		b->val = a[0];
		for (int i = 1; i < n; i++)
		{
			//fread(&tempp, sizeof(int), 1, f1);
			//addison(root, tempp);
			addison(root,a[i]);

		}
		free(a);
		a = (int*)calloc(n, sizeof(int));
		n = 0;
		printMe(root, a, &n);
		/*
		for (int i = 0; i < n; i++)
		{
			printf("%d  ", a[i]);
		}
		printf("\n");
		*/
		fwrite(a, sizeof(int), n, f2);
		free(a);
	}
	return 0;
}