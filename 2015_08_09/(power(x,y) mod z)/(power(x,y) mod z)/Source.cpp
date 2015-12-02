#include<stdio.h>
typedef struct result
{
	int ans;
	int v;
}Answer;
struct test
{
	int x,y,z;
	int answer;
	int v;
}testDB[10]={
	{3,2,5,4,1},
	{98,2,5,4,1},
	{3,0,1,0,1},
	{35,5,7,0,1},
	{32,16,9,4,1},
	{16,16,23,6,1},
	{-23,2,5,0,0},
	{2,-2,5,0,0},
	{3,2,-5,0,0},
	{102,52,3,0,1}
};
int isValid(int x,int y,int z)
{
	if(x<0||y<0||z<0)
		return 0;
	return 1;
}
Answer powerMod(int x,int y,int z)
{
	int ans=1;
	int temp=x;
	Answer res;
	if(isValid(x,y,z))
		res.v=1;
	else
	{
		res.v=0;
		return res;
	}
	if(y==0&&z>1)
	{
	    res.ans=1;
		return res;
	}
	else if(y==0)
	{
		res.ans=0;
		return res;
	}
	while(y!=0)
	{
	    if(y%2)
	        ans=ans*temp;
	    temp=(temp*temp)%z;
	    y=y/2;
	    if(ans>z)
	        ans=ans%z;
	}
	res.ans=ans;
	return res;
}
int compare(int i,Answer res)
{
	if(testDB[i].v!=res.v)
		return 0;
	if(res.v==0)
		return 1;
	if(testDB[i].answer==res.ans) 
		return 1;
	else 
		return 0;
}
int main()
{
	int i;
	Answer res;
	for(i=0;i<10;i++)
	{
		res=powerMod(testDB[i].x,testDB[i].y,testDB[i].z);
		if(compare(i,res))
			printf("Valid\n");
		else
			printf("Invalid\n");
	}
	return 0;
}