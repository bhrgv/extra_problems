#include<stdio.h>
#include<malloc.h>
/*
Test Case Database contains the Input Array , Output Array and the Length of the Input Array
The Resultant Generated from the Input Array is Compared to the Output Array given, If Both of them 
Matched then the Execution is Correct and thus Display Valid or else Display Invalid
*/
struct test
{
	int input[100];
	int length;
	int output[100];
}testDB[10]={
	{{1,2,3,4,5}, 5 ,{120,60,40,30,24}},//a general sorted array.
	{{21,24,35,43}, 4 ,{36120,31605,21672,17640}},//a sorted array with some big integers.
	{{-2,-5,-1,-3,-7,-9}, 6 ,{-945,-378,-1890,-630,-270,-210}},//array having only negative integers.Even length array.
	{{-12,3,45,-9}, 4 ,{-1215,4860,324,-1620}},//Array with a mix of negative and positive numbers.
	{{-2,-9,-14,-7,-1}, 5 ,{882,196,126,252,1764}},//negative integer array of odd length.
	{{10,20,0,30,40}, 5 ,{0,0,240000,0,0}},//array with single occurence of zero.
	{{1,2,3,4,5,6,7,0,0}, 9 ,{0,0,0,0,0,0,0,0,0}},//array with two occurences of zero.
	{{-5,6,0,4,0,0,9}, 7 ,{0,0,0,0,0,0,0}},//array with more than two occurences of zero.
	{{2,2,2,2,2}, 5 ,{16,16,16,16,16}},//array with all same elements
	{{32}, 1 ,{0}}//array of length 1. here the output is considered as zero as there are no other elements.
};
int* productArray(int* ip,int nos)
{
	int *op;//,*b,*c;
	int i,d,j,d1;
	op=(int*)malloc(nos*sizeof(int));
	for(i=0;i<nos;i++)
	{
		d=d1=1;
		if(i==0)
		{
			for(j=1;j<nos;j++) //Finding Product of the Right Hand Side
			d*=ip[j];
			if(nos>1)
				op[i]=d;
			else
				op[i]=0;
		}
		else if(i==nos-1)
		{
			for(j=nos-2;j>=0;j--) //Finding Product of the Left Hand Side
			d*=ip[j];
			op[i]=d;
		}
		else
		{
			for(j=i-1;j>=0;j--)		//Finding Product of the Left Hand Side
			d*=ip[j];
			for(j=i+1;j<nos;j++)	//Finding Product of the Right Hand Side
			d1*=ip[j];
			op[i]=d*d1;
		}
	}
	return op;
}
int isCheck(int *op,int i)
{
	int j;
	for(j=0;j<testDB[i].length;j++)
		if(testDB[i].output[j]!=op[j])
			return 0;
	return 1;
}
int main()
{
	int *op;
	int j,i;
	for(i=0;i<10;i++)
	{
		op=productArray(testDB[i].input,testDB[i].length);
		if(isCheck(op,i))
			printf("valid\n");
		else
			printf("Invalid\n");
		free(op);
	}
	return 0;
}