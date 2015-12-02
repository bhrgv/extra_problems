#include<stdio.h>
#include<malloc.h>
typedef struct ans
{
	int r;
	int flag;
}Answer;
struct test
{
	char input[1000];
	int output;
	int v;
}testDB[13]={
	{"125,36",125,1},//Normal Input.
	{"    125,36  ",125,1},//Input With Spaces at Starting and Ending.
	{"125    ,36",125,1},//Input with Spaces after the First Number.
	{"125,    36",125,1},//Input with Spaces After the Comma and Before the Second Number.
 	{"-125,+36",36,1},//Input with Signs.
	{"    -125,36",36,1},//Sign and Space in the Beginning.
	{"-125    ,36  ",36,1},//Sign and Spaces After each Number.
	{"125,    +36",125,1},//Sign and Space before the Second Number.
	{"    125   ,    36   ",125,1},//Spaces before and After both the Digits.
	{"    -125   ,    +36   ",36,1},//Spaces before and After both the Digits with Signs.
	{"*125,/36",0,0},//Signs Other than + and -.Invalid.
	{"100$1  ,123",0,0},//Input with sppecial characters.Invalid.
	{"",0,0}//Empty string as input.Considered invalid.
};
int isValid(char* str)
{
	int i=0;
	while(str[i]==' ')  // Ignoring Spaces Starting of the String
		i++;
	if(str[i]==',')  //If the Comma Preceedes the First Number then the String is Invalid
		return 0;
	if(str[i]=='-'||str[i]=='+')		//Sign Bits are Allowed
		i++;
	while((((int)str[i]<57&&(int)str[i]>47)||((int)str[i]==32))&&str[i]!=','&&str[i]!=' '&&str[i]!='\0')
	{
		i++;	//Allowing only Numbers
	}
	while(str[i]==' ') //Skipping Spaces Present After the First Number and Before the Comma
		i++;
	if(str[i]=='\0') //If encounter Carriage Return then Invalid String no Second Number present
		return 0;
	if(str[i]==',') //comma after a Number is Valid
			i++;
	else 
		return 0; //if Comma not Present then Invalid String
	while(str[i]==' ') //Skip spaces before Second Number
		i++;
	if(str[i]=='-'||str[i]=='+') //Sign bits for Second Number
		i++;
	while((((int)str[i]<57&&(int)str[i]>47)||((int)str[i]==32))&&str[i]!=','&&str[i]!=' '&&str[i]!='\0')
	{
		i++; // Allowing only Numbers
	}
	while(str[i]==' ') //Skipping Spaces after the Second Number
		i++;
	if(str[i]==',') //Should not Contain Second Comma
		return 0;
	if(str[i]=='\0') // IF Encounters Carriage Return then Valid String
		return 1;
}
int* toNumber(char* str) //Function to Convert String into Two Different Numbers
{
	int i=0,n,sflg=0;
	int *ans=(int*)malloc(2*sizeof(int));
	while(str[i]==' ') //Skipping Spaces
		i++;
	n=0;
	if(str[i]=='-') //If Negative Number
	{
		i++;
		sflg=1;
	}
	if(str[i]=='+') //If positive No Need to update the Flag
		i++;
	while(str[i]!=',') //Determining the First Number
	{
		if(str[i]!=' ')
			n=n*10+(int)str[i]-48;
		i++;
	}
	i++;
	if(sflg==1) //Convert into Negative if flg is Updated
		n*=-1;
	ans[0]=n;
	n=0;
	while(str[i]==' ')
		i++;
	if(str[i]=='-') //Checking the Sign for Second Number
	{
		i++;
		sflg=1;
	}
	else
		sflg=0;
	if(str[i]=='+')
		i++;
	while(str[i]!='\0')
	{
		if(str[i]!=' ')
			n=n*10+(int)str[i]-48;
		i++;
	}
	if(sflg==1)
		n*=-1;
	ans[1]=n;
	return ans;
}
Answer max(char* str)
{
	int *num;
	Answer res;
	res.flag=1;
	if(isValid(str))
	{
		num=toNumber(str);
		if(num[0]>num[1])
			res.r=num[0]; 
		else 
			res.r=num[1];
	}
	else
	{
		//printf("Invalid Input Format\n");
		res.flag=0;
	}
	return res;
}
int isCheck(Answer ans,int i)
{
	if(ans.flag==0&&testDB[i].v==0)
		return 1;
	if(ans.flag!=testDB[i].v)
		return 0;
	if(ans.r!=testDB[i].output)
		return 0;
	return 1;
}
int main()
{
	Answer ans;
	int i;
	for(i=0;i<13;i++)
	{
		ans=max(testDB[i].input);
		if(isCheck(ans,i))
			printf("Valid\n");
		else
			printf("Invalid\n");
	}
	return 0;
}