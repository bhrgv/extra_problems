#include<stdio.h>
#include<malloc.h>
typedef struct ans
{
	int *r;
	int flag;
}Answer;
struct test
{
	char input[1000];
	char ans[10001];
	int v;
}testDB[13]={
	{"125,36","125",1},//Normal Input.
	{"    125,36  ","125",1},//Input With Spaces at Starting and Ending.
	{"125    ,36","125",1},//Input with Spaces after the First Number.
	{"125,    36","125",1},//Input with Spaces After the Comma and Before the Second Number.
 	{"-125,+36","+36",1},//Input with Signs.
	{"    -125,36","36",1},//Sign and Space in the Beginning.
	{"-125    ,36  ","36",1},//Sign and Spaces After each Number.
	{"125,    +36","125",1},//Sign and Space before the Second Number.
	{"    125   ,    36   ","125",1},//Spaces before and After both the Digits.
	{"    -125   ,    +36   ","+36",1},//Spaces before and After both the Digits with Signs.
	{"*125,/36","",0},//Signs Other than + and -.Invalid.
	{"100$1  ,123","",0},//Input with sppecial characters.Invalid.
	{"","",0}//Empty string as input.Considered invalid.
};
int isValid(char* str) // Same as in Method 1
{
	int i=0;
	if(str[i]=='\0')
		return 0;
	while(str[i]==' ')
		i++;
	if(str[i]==',')
		return 0;
	if(str[i]=='-'||str[i]=='+')
		i++;
	while((((int)str[i]<57&&(int)str[i]>47)||((int)str[i]==32))&&str[i]!=','&&str[i]!=' '&&str[i]!='\0')
	{
		i++;
	}
	while(str[i]==' ')
		i++;
	if(str[i]=='\0')
		return 0;
	if(str[i]==',')
			i++;
	else 
		return 0;
	while(str[i]==' ')
		i++;
	if(str[i]=='-'||str[i]=='+')
		i++;
	while((((int)str[i]<57&&(int)str[i]>47)||((int)str[i]==32))&&str[i]!=','&&str[i]!=' '&&str[i]!='\0')
	{
		i++;
	}
	while(str[i]==' ')
		i++;
	if(str[i]==',')
		return 0;
	if(str[i]=='\0')
		return 1;
}
int** len(char* str) //Finding the String Structure
{
	int** ans;
	int i;
	ans=(int**)malloc(2*sizeof(int)); //Two Row for two Number
	for(i=0;i<2;i++)
		ans[i]=(int*)malloc(3*sizeof(int));
	/*
		First Column contains the Sign Bit of the Number if Negative 1 or else 0
		Second column contains the Starting index of the Number
		Third Column contains the Ending index of the Number
	*/
	ans[0][0]=0;
	ans[1][0]=0;
	i=0;
	while(str[i]==' ')
		i++;
	if(str[i]=='-')
	{
		ans[0][0]=1;
		i++;
	}
	ans[0][1]=i;
	while(str[i]!=' '&&str[i]!=',')
		i++;
	ans[0][2]=i-1;
	while(str[i]!=',')
		i++;
	if(str[i]==',')
		i++;
	while(str[i]==' ')
		i++;
	if(str[i]=='-')
	{
		ans[1][0]=1;
		i++;
	}
	ans[1][1]=i;
	while(str[i]!=' '&&str[i]!='\0')
		i++;
	ans[1][2]=i-1;
	return ans;
}
Answer max(char* str)
{
	int **ans=NULL;
	Answer ret;
	ret.flag=1;
	int flg;
	int i,j;
	int *res=(int*)malloc(2*sizeof(int));
	res[0]=0;
	res[1]=0;
	if(isValid(str))
	{
		ans=len(str);
		if(ans[0][0]==1&&ans[1][0]==1)
			flg=1;
		else if(ans[0][0]==1&&ans[1][0]==0)
			flg=2;
		else if(ans[0][0]==0&&ans[1][0]==1)
			flg=3;
		else
			flg=0;
		if((ans[0][2]-ans[0][1]+1)>(ans[1][2]-ans[1][1]+1))
		{
			if(flg==0||flg==3)
			{
				res[0]=ans[0][1];
				res[1]=ans[0][2];
			}
			else
			{
				res[0]=ans[1][1];
				res[1]=ans[1][2];
			}
		}
		else if((ans[0][2]-ans[0][1]+1)<(ans[1][2]-ans[1][1]+1))
		{
			if(flg==2||flg==0)
			{
				res[0]=ans[1][1];
				res[1]=ans[1][2];
			}
			else
			{
				res[0]=ans[0][1];
				res[1]=ans[0][2];
			}
		}
		else
		{
			i=ans[0][1];
			j=ans[1][1];
			res[0]=ans[0][1];
			res[1]=ans[0][2];
			while(str[i]!=','&&str[i]!='\0')
			{
				if((int)str[i]>(int)str[j])
				{
					if(flg==0||flg==3)
					{
						res[0]=ans[0][1];
						res[1]=ans[0][2];
					}
					else
					{
						res[0]=ans[1][1];
						res[1]=ans[1][2];
					}
					break;
				}
				else if((int)str[i]<(int)str[j])
				{
					if(flg==2||flg==0)
					{
						res[0]=ans[1][1];
						res[1]=ans[1][2];
					}
					else
					{
						res[0]=ans[0][1];
						res[1]=ans[0][2];
					}
					break;
				}
				else
				{
					i++;
					j++;
				}
			}
		}
	}
	else
	{
		//printf("Invalid Format\n");
		ret.flag=0;
	}
	free(ans);
	ret.r=res;
	return ret;
}
int isCheck(Answer res,int i)
{
	int j,z=0;;
	if(res.flag==0&&testDB[i].v==0)
		return 1;
	if(res.flag!=testDB[i].v)
		return 0;
	for(j=res.r[0];j<=res.r[1];j++,z++)
		if(testDB[i].input[j]!=testDB[i].ans[z])
			return 0;
	return 1;
}
int main()
{
	Answer res;
	int i,j;
	for(j=0;j<13;j++)
	{
		res=max(testDB[j].input);
		if(isCheck(res,j))
			printf("Valid\n");
		else
			printf("Invalid\n");
		free(res.r);
	}
	return 0;
}