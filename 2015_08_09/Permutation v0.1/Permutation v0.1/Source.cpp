#include<stdio.h>
#include<malloc.h>
#define SIZE 10
struct test 
{
	char input[1000000];
	int output;
	int valid;
}testDB[SIZE]={
	{"22",0,1},
	{"5143",19,1},
	{"213",2,1},
	{"   213",2,1},
	{"213   ",2,1},
	{"    213   ",2,1},
	{"-213",-1,0},
	{"abc",-1,0},
	{"23$",-1,0},
	{"236",0,1},
};
void swap(int *x, int *y)
{
    int temp;
	if(x!=y)
	{
		temp = *x;
		*x = *y;
		*y = temp;
	}
}
int factorial(int n)
{
	if(n==0||n==1)
		return 1;
	else
		return n*factorial(n-1);
}
void add_to_list(int* a,int* arr,int size)
{
	int i,num=0;
	for(i=0;i<size;i++)
		num=num*10+a[i];
	for(i=0;arr[i]!=-1;i++)
		if(arr[i]==num)
			return;
	arr[i]=num;
}
void permute(int *a, int l, int r,int* arr,int n)
{
   int i;
   if (l == r)
     add_to_list(a,arr,n);
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          permute(a, l+1, r,arr,n);
          swap((a+l), (a+i));
       }
   }
}
int isValid(char* str)
{
	int i=0;
	while(str[i]==' ')
		i++;
	while((int)str[i]>=48&&(int)str[i]<=57)
		i++;
	while(str[i]==' ')
		i++;
	if(str[i]!='\0')
		return 0;
	return 1;
}
void bubbleSort(int* a,int n)
{
	int i,j;
	for(i=0;a[i]!=-1&&i<n;i++)
	{
	}
	if(i!=n)
		n=i;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				a[j]=a[j]+a[j+1];
				a[j+1]=a[j]-a[j+1];
				a[j]=a[j]-a[j+1];
			}
		}
	}
}
int linearSearch(int* a,int k,int n)
{
	int i;
	for(i=0;i<n;i++)
		if(a[i]==k)
			return i;
}
int* noOfDigits(char* str)
{
	int i=0,j=0,num=0;
	int* res=(int*)calloc(2,sizeof(int));
	while(str[i]!='\0')
	{
		if(str[i]!=' ')
		{
			j++;
			num=num*10+(int)str[i]-48;
		}
		i++;
	}
	res[0]=num;
	res[1]=j;
	return res;
}
int getDigits(char* num)
{
	if(isValid(num))
	{
		int *arr=noOfDigits(num);
		int no_digits=arr[1];
		int number=arr[0];
		free(arr);
		arr=(int*)malloc(factorial(no_digits)*sizeof(int));
		int *digits=(int*)malloc(no_digits*sizeof(int));
		int temp=number;
		int i=0,j;
		while(temp)
		{
			digits[i++]=temp%10;
			temp/=10;
		}
		int m=factorial(no_digits);
		for(i=0;i<m;i++)
			arr[i]=-1;
		permute(digits,0,no_digits-1,arr,no_digits);
		bubbleSort(arr,m);
		return linearSearch(arr,number,m);
	}
	else
		return -1;
}
int compare(int i,int ans)
{
	if(testDB[i].valid==0&&ans==-1)
		return 1;
	else if(testDB[i].output==ans)
		return 1;
	else
		return 0;
}
int main()
{
	int i;
	for(i=0;i<SIZE;i++)
	{
		int ans=getDigits(testDB[i].input);
		if(compare(i,ans))
			printf("Valid\n");
		else
			printf("Invalid\n");
	}
	return 0;
}