#include<stdio.h>
#include<malloc.h>
struct test
{
	char input[1000];
	char input2[1000];
	char output[1000];
	int v;
}testDB[11]={
	{"101","101","1010",1},//Normal binary number in string format.
	{"0011","0011","00110",1},//binary number with leading zeros.
	{"   1110","   1110","11100",1},//binary number with leading spaces. It's valid.
	{"10101   ","10101   ","101010",1},//binary number with trailing spaces. It's valid.
 	{"1 0 111","1 0 111","",0},//binary number with spaces in between.It's considered invalid.
	{"abc","abc","",0},//alphabets in place of zeros and ones.Invalid
	{"120","120","",0},//not a proper binary number.Invalid
	{"  10111  ","  10111  ","101110",1},//Binary number with both trailing and leading zeros.Valid
	{"10000","10000","100000",1},//binary number with trailing zeros.
	{"100$1  ","100$1  ","",0},//Input with sppecial characters.Invalid.
	{"","","",0}//Empty string as input.Considered invalid.
};
typedef struct ans // Making a Structure to Return more than two Values from the Function
{
	char *c;  //Stores the Address of the String 
	int flag;	//Indicates the Result is Valid or Not
}Answer;
int isValid(char* num1,char* num2)
{
	int i=0;
	if(num1[0]=='\0'||num2[0]=='\0')
		return 0;
	while(num1[i]==' ') //Spaces at the Starting of the Number is allowed.
		i++;
	while((int)num1[i]==48||(int)num1[i]==49) // Digits should be 1 or else 0 only
		i++;
	while(num1[i]==' ') //Spaces after the Number are Allowed
		i++;
	if(num1[i]!='\0') //No other Digits or Character is allowed after the End of Spaces Except Carriage Return 
		return 0;
	i=0;
	while(num2[i]==' ') // All Above Step for the Second Number.
		i++;
	while((int)num2[i]==48||(int)num2[i]==49)
		i++;
	while(num2[i]==' ')
		i++;
	if(num2[i]!='\0')
		return 0;
	else 
		return 1;
}
int nod(char* str) // Counting no of Digits Present in a String
{
	int i;
	int j=0;
	for(i=0;str[i]!='\0';i++)
	{
		if((int)str[i]==48||(int)str[i]==49)
			j++;
	}
	return j;
}
int len(char* str)		//Counting the Length of the String 
{
	int i;
	for(i=0;str[i]!='\0';i++)
	{
	}
	return i;
}
Answer add(char* num1,char* num2)
{
	char *ans;
	Answer res;
	res.flag=1;
	res.c=NULL;
	int size1=nod(num1);
	int size2=nod(num2);
	int d=0,i=0,size=0;
	if(isValid(num1,num2))
	{
		if(size1>size2)
			size=size1;
		else
			size=size2; 
		// Assigning the New String The Size greater among the Two Number.
		size1=len(num1);
		size2=len(num2);
		//Finding Actual String Length with Spaces 
		ans=(char*)malloc((size+2)*sizeof(char)); //New String Size increased by two for Carry and Carriage Return.
		size1--;
		size2--;
		while(num1[size1]== ' ')
			size1--;
		while(num2[size2]== ' ')
			size2--;
		// Eliminating Spaces
		while(size1>=0&&size2>=0)
		{
			char c;
			if((int)num1[size1]!=32&&(int)num2[size2]!=32) //Addition of Number to be Done if the Character encountered is a Digit.
			{
				d=(int)num1[size1--]-48+(int)num2[size2--]-48+d;
				c=(char)(d%2+48);
				ans[i++]=c;
				d/=2;
			}
			if(num1[size1]==' ') //Size decreased if Space if Encoutered without Performing any Operation
				size1--;
			if(num2[size2]==' ')
				size2--;
		}
		while(size1>=0) //If First Number is Still Left to be Computed 
		{
			if((int)num1[size1]==48||(int)num1[size1]==49)
			{
				d=(int)num1[size1]-48+d;
				ans[i++]=(char)(d%2+48);
				d/=2;
			}
			size1--;
		}
		while(size2>=0) //If Second Number is Still Left to be Computed 
		{
			if((int)num2[size2]==48||(int)num2[size2]==49)
			{
				d=(int)num2[size2]-48+d;
				ans[i++]=(char)(d%2+48);
				d/=2;
			}
			size2--;
		}
		if(i==size) //Inserting Carry in the String .
			ans[i++]=(char)(d+48);
		ans[i]='\0'; //Finishing the String with a Carriage Return 
		i=0;
		int j=size;
		while(i<j) // Reversing the String
		{
			char c=ans[i];
			ans[i]=ans[j];
			ans[j]=c;
			i++;
			j--;
		}
	}
	else
	{
		//printf("Invalid Input Format\n");
		 // No String Could be Evaluated
		ans=NULL;
		res.flag=0; //Flag set to indicate it is an Error
	}
	res.c=ans; //Resultant String Sent back to Main()
	return res;
}
int compare(int i,Answer res)
{
	int j;
	if(testDB[i].v==0&&res.flag==0)
		return 1;
	if(testDB[i].v!=res.flag)
		return 0;
	for(j=0;testDB[i].output[j]!='\0';j++)
		if(res.c[j]!=testDB[i].output[j])
			return 0;
	return 1;
}
int main()
{
	int i;
	for(i=0;i<11;i++)
	{
		Answer res=add(testDB[i].input,testDB[i].input2);
		if(compare(i,res))
			printf("Valid\n");
		else
			printf("Invalid\n");
		free(res.c);
	}
	return 0;
}