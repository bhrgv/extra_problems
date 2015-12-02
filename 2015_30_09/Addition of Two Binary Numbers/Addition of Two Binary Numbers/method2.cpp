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
typedef struct ans
{
	char *c; // To store the Address of the Resultant String
	int flag; // To indicate the Resultant Computation is Valid or Not
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
int nod(char* str) // To Calculate Number of Digits Present in the String
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
Answer add(char* num1,char* num2)
{
	Answer res;
	res.flag=1;
	int i,j,d;
	int size1,size2,size;
	if(isValid(num1,num2))
	{
		// Copy the Binary Number into an Array
		int* arr1=(int*)malloc(nod(num1)*sizeof(int));
		int* arr2=(int*)malloc(nod(num2)*sizeof(int));
		char *ans;
		for(i=0,j=0;num1[i]!='\0';i++)
		{
			if(num1[i]=='1'||num1[i]=='0')
				arr1[j++]=(int)num1[i]-48;
		}
		size1=j;
		for(i=0,j=0;num2[i]!='\0';i++)
		{
			if(num2[i]=='1'||num2[i]=='0')
				arr2[j++]=(int)num2[i]-48;
		}
		size2=j;
		d=0;
		if(size1>size2)
			size=size1;
		else
			size=size2;
		size1--,size2--;
		ans=(char*)malloc((size+2)*sizeof(char));
		i=0;
		//Start Calculating the Sum of Binary Numbers from the One's Place of Binary Numbers
		while(size1>=0&&size2>=0)
		{
			d=arr1[size1--]+arr2[size2--]+d;
			ans[i++]=(char)(d%2+48);
			d/=2;
		}
		while(size1>=0) // If Second Binary Number has been Added, Computation of Carry and First Binary Number
		{
			d=arr1[size1--]+d;
			ans[i++]=(char)(d%2+48);
			d/=2;
		}
		while(size2>=0) // If First Binary Number has been Added, Computation of Carry and Second Binary Number
		{
			d=arr2[size2--]+d;
			ans[i++]=(char)(d%2+48);
			d/=2;
		}
		ans[i++]=(char)(d+48); //  Inserting the Carry into the Answer String
		ans[i]='\0';
		i=0;
		j=size;
		while(i<j) // Reversing the String
		{
			char c=ans[i];
			ans[i]=ans[j];
			ans[j]=c;
			i++,j--;
		}
		res.c=ans;
	}
	else
	{
		//printf("Invalid Input Format \n");
		res.c=NULL;
		res.flag=0; // FLag for Invalid Input Format
	}
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