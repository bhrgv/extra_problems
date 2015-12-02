#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define SIZE 110
#define INP 16
struct test
{
	char input[100];
	char output[100];
	int valid;
}testDB[INP]={
	{"24/03/1995","Twenty Four of March One Thousand Nine Hundred Ninety Five",1},
	{"         24/03/1995","Twenty Four of March One Thousand Nine Hundred Ninety Five",1},
	{"24/03/1995         ","Twenty Four of March One Thousand Nine Hundred Ninety Five",1},
	{"  24/03/1995   ","Twenty Four of March One Thousand Nine Hundred Ninety Five",1},
	{"32/03/1995","",0},
	{"0/03/1995","",0},
	{"21/0/1995","",0},
	{"2/03/0","",0},
	{"29//1995","",0},
	{"29/2/","",0},
	{"/2/1995","",0},
	{"29/2/2000","Twenty Nine of February Two Thousand",1},
	{"29/2/2016","Twenty Nine of February Two Thousand Sixteen",1},
	{"29/2/2003","",0},
	{"abc","",0},
	{"@#$","",0}
};
typedef struct result
{
	char* ans;
	int v;
}Answer;
int isLeapYear(int y)
{
	if(y%400==0||(y%4==0&&y%100!=0))
		return 1;
	else
		return 0;
}
int* isValidInput(char* str)
{
	int i=0,dd=0,mm=0,yy=0,d,flg=0;
	int* meta=(int*)calloc(3,sizeof(int));
	while(str[i]==' ')
		i++;
	while(str[i]!='\0')
	{
		if(str[i]!=' ')
		{
			
			if(str[i]=='/')
			{
				flg++;
			}
			else if((int)str[i]<48||(int)str[i]>57)
				return NULL;
			else if(flg==0)
			{
				d=(int)str[i]-48;
				dd=dd*10+d;
			}
			else if(flg==1)
			{
				d=(int)str[i]-48;
				mm=mm*10+d;
			}
			else if(flg==2)
			{
				d=(int)str[i]-48;
				yy=yy*10+d;
			}
		}
		else 
			break;
		i++;
	}
	if(flg>2)
		return NULL;
	while(str[i]==' ')
		i++;
	if(str[i]!='\0')
		return NULL;
	if(dd>31||dd==0)
		return NULL;
	if(mm>12||mm==0)
		return NULL;
	if(yy==0)
		return NULL;
	switch(mm)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		if(dd>30)
			return NULL;
		break;
	case 2:
		if(isLeapYear(yy))
		{
			if(dd>29)
				return NULL;
		}
		else
		{
			if(dd>28)
				return NULL;
		}
	}
	meta[0]=dd,meta[1]=mm,meta[2]=yy;
	return meta;
}
int appendString(char* date,int value,int index)
{
	/* The first string is not used, it is to make array indexing simple */
    char *single_digits[] = { "", "One", "Two", "Three", "Four",
                              "Five", "Six", "Seven", "Eight", "Nine"};
 
    /* The first string is not used, it is to make array indexing simple */
    char *two_digits[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                     "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
 
    /* The first two string are not used, they are to make array indexing simple*/
    char *tens_multiple[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty",
                             "Sixty", "Seventy", "Eighty", "Ninety"};
 
    char *tens_power[] = {"Hundred", "Thousand"};
	int d;
	int j;
	while(value)
	{
		j=0;
		if(value>1000)
		{
			d=value/1000;
			value-=d*1000;
			while(single_digits[d][j]!='\0')
					date[index++]=single_digits[d][j++];
			date[index++]=' ';
			j=0;
			while(tens_power[1][j]!='\0')
					date[index++]=tens_power[1][j++];
			date[index++]=' ';
		}
		else if(value>100)
		{
			d=value/100;
			value-=d*100;
			while(single_digits[d][j]!='\0')
					date[index++]=single_digits[d][j++];
			date[index++]=' ';
			j=0;
			while(tens_power[0][j]!='\0')
					date[index++]=tens_power[0][j++];
			date[index++]=' ';
		}
		else
		{
			if(value>=10&&value<20)
			{
				while(two_digits[value%10][j]!='\0')
					date[index++]=two_digits[value%10][j++];
			}
			else
			{
				
				d=value%10;
				value/=10;
				while(tens_multiple[value][j]!='\0')
					date[index++]=tens_multiple[value][j++];
				if(j!=0)
					date[index++]=' ';
				j=0;
				while(single_digits[d][j]!='\0')
					date[index++]=single_digits[d][j++];
			}
			break;
		}
	}
	return index;
}
Answer printDate(char* str)
{
	int* meta=isValidInput(str);
	char *date;
	date=(char*)calloc(SIZE,sizeof(char));
	int i=0;
	Answer res;
	if(meta!=NULL)
	{
		i=appendString(date,meta[0],i);
		date[i++]=' ';
		date[i++]='o';
		date[i++]='f';
		date[i++]=' ';
		int j=0;
		char *month[] = {"","January", "February","March","April","May","June","July","August","September","October","November","December"};
		while(month[meta[1]][j]!='\0')
			date[i++]=month[meta[1]][j++];
		date[i++]=' ';
		i=appendString(date,meta[2],i);
		date[i]='\0';
		res.ans=date;
		res.v=1;
	}
	else
	{
		res.v=0;
		free(date);
	}
	free(meta);
	return res;
}
int compare(int i,Answer res)
{
	if(testDB[i].valid!=res.v)
		return 0;
	else if(res.v==0)
		return 1;
	else
	{
		int j=0;
		while(testDB[i].output[j]!='\0')
		{
			if(res.ans[j]!=testDB[i].output[j])
				return 0;
			j++;
		}
	}
	return 1;
}
int main()
{
	int i;
	for(i=0;i<INP;i++)
	{
	Answer op=printDate(testDB[i].input);
	if(compare(i,op))
		printf("Valid\n");
	else
		printf("Invalid\n");
	if(op.v==1)
		free(op.ans);
	}
	return 0;
}