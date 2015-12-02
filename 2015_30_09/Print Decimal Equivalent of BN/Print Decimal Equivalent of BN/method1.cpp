#include<stdio.h>
struct test
{
	char input[1000];
	int output;
	int v;
}testDB[12]={
	{"101",5,1},//Normal binary number in string format.
	{"0011",3,1},//binary number with leading zeros.
	{"   1110",14,1},//binary number with leading spaces. It's valid.
	{"10101   ",21,1},//binary number with trailing spaces. It's valid.
 	{"1 0 111",0,0},//binary number with spaces in between.It's considered invalid.
	{"abc",0,0},//alphabets in place of zeros and ones.Invalid
	{"120",0,0},//not a proper binary number.Invalid
	{"  10111  ",23,1},//Binary number with both trailing and leading zeros.Valid
	{"10000",16,1},//binary number with trailing zeros.
	{"100$1  ",0,0},//Input with sppecial characters.Invalid.
	{"",0,0},//Empty string as input.Considered invalid.
	{"0",0,1}//Binary String Equivalent to Zero
};
int isValid(char *str)
{
	int flg=0,strt=0; //strt is maintained to check the Spaces, flg is flag variable to determine input is Valid or not
	int i;
	for(i=0;str[i]!='\0';i++)
	{
		flg=1;
		if((int)str[i]==32)
		{
			if(strt==1) // if Spaces is Occuring After the Occurance of the Digits.
				strt++;
		}
		else if((int)str[i]==48||(int)str[i]==49) //Only 0's and 1's are allowed.
		{
			if(strt==0) //if Number has Occured for First Time then strt is Increemented.
				strt++;
			if(strt==2)	//if Space has Occured between the Digits.
			{
				flg=0;
				break;
			}
		}
		else //If Input has Characters Other than 0's and 1's.
		{
			flg=0;
			break;
		}
	}
	return flg;
}
int len(char* str) //Function to find the String Length
{
	int i;
	for(i=0;str[i]!='\0';i++)
	{
	}
	return i;
}
int power(int val,int n)	//Function to find the Power.
{
	if(n==0)
		return 1;
	else
		return val*power(val,n-1);
}
int eval(char* str)	//Function to Evaluate the Binary Number and Convert it into Decimal Equivalent.
{
	int j=len(str)-1;
	int i=0,n;
	char c;
	if(!isValid(str))	//Checking the Validity of the Given Input.
	{
		//printf("Invalid Input\n");
		return -1;
	}
	while(i<j)	//Reversing the String.
	{
		c=str[i];
		str[i]=str[j];
		str[j]=c;
		i++;
		j--;
	}
	n=0;
	i=0;
	while(str[i]==' ') //Eliminating Spaces if Present.
		i++;
	for(j=0;str[i]!='\0';j++)
	{
		if((int)str[i]==48||(int)str[i]==49) //Allowing only 0's and 1's , Avoiding Occurances of Spaces.
		n=n+((int)str[i]-48)*(power(2,j));	//Converting Input Character to Integer and Adding ut to n (Decimal Equivalent)
		i++;
	}
	return n;
}
int isCheck(int res,int i)
{
	if(res==-1&&testDB[i].v==0)
		return 1;
	if((res!=-1&&testDB[i].v==0)||(res==-1&&testDB[i].v!=0))
		return 0;
	if(res!=testDB[i].output)
		return 0;
	return 1;
}
int main()
{
	char str[50];
	int i,res;
	for(i=0;i<12;i++)
	{
		res=eval(testDB[i].input);
		if(isCheck(res,i))
			printf("valid\n");
		else
			printf("Invalid\n");
	}
		return 0;
}
