#include<stdio.h>
#include<malloc.h>
/* Taking a Test case Database where Input would be Updated and Would be Checked to the Required output if the Output is Matched
	then it will print Valid or it will print Invalid for a Incorrect Execution of a Test Case .
*/
struct test
{
	int input[100]; //Input Array
	int length;	//Lenght of a Array , Would be Same for Input and Output Array
	int output[100]; //Output Array or Excepted Output
}testDB[10]={
	{{1,2,3,6,5,4,7}, 7 ,{1,2,3,4,5,6,7}},//ascending order.reversepart in middle of input.
	{{7,2,4,5,1}, 5 ,{7,5,4,2,1}},//descending order.reverse part in middle of input. 
	{{98,87,76,59,106,132}, 6 ,{59,76,87,98,106,132}},//ascending.reverse part at begining.
	{{56,57,58,59,53,52}, 6 , {59,58,57,56,53,52}},//descending.reverse part at begining.
	{{1,7,6,5,4,3,2}, 7 ,{1,2,3,4,5,6,7}},//ascending.reverse part at ending.
	{{-2,-3,-4,-5,-6,-1}, 6 ,{-6,-5,-4,-3,-2,-1}},//ascending.having negative numbers.
	{{8,7,7,6,5,4,8}, 7 ,{4,5,6,7,7,8,8}},//ascending.Same number at start and end.
	{{5,1,2,2,3,4,5}, 7 ,{5,5,4,3,2,2,1}},//descending.Same number at start and end.
	{{2,2,2,2}, 4 ,{2,2,2,2}},//all values are same.
	{{2,-5,-10,-7}, 4 ,{2,-5,-7,-10}} //descending. mix of negative and positive numbers.
};
int isSort(int* array,int n)
{
	int i=0;
	int j=n-1;
	if(array[i]>array[j])	//If First Element is Greater than the Last Element then it is a Descending Order
		return 1;
	else if(array[i]<array[j])   //If First Element is Less than the Last Element then it is a Ascending Order
		return 0;
	else	//If Elements are Equal 
	{
		//Avoid Duplications increment the Array till the Adjacent Elements are Equal
		while(array[i]==array[i+1]) 
			i++;
		while(array[j]==array[j-1])
			j--;
		i++;
		j--;
		if(array[i]>array[j])	//COndition for Descending Order
		return 0;
		else if(array[i]<array[j])  //COndition for Descending Order
		return 1;
	}
}
void fix(int* array,int n)
{
	int i,j,flg=0;
	int first,last,c;
	if(isSort(array,n)) //Determining the type of Sorting 
	{
		// For Descending Order type of Sorting 
		for(i=0;i<n-1;i++)
		{
			if(array[i]<array[i+1])
			{
				flg=1;
				break;
			}
		}
		first=i;
		while(i<n&&flg)
		{
			if(array[i]<=array[i+1])
				i++;
			else
				break;
		}
		last=i;
		if(i==n)
			last=n-1;
	}
	else
	{
		//For Ascending Order type of Sorting
		for(i=0;i<n-1;i++)
		{
			if(array[i]>array[i+1])
			{
				flg=1;
				break;
			}
		}
		first=i;
		while(i<n-1&&flg)
		{
			if(array[i]>=array[i+1])
				i++;
			else
				break;
		}
		last=i;
	}
	i=first;
	j=last;
	while(i<j)
	{
		c=array[i];
		array[i]=array[j];
		array[j]=c;
		i++;
		j--;
	}
}
int isCheck(int i)
{
	int j;
	// The Modified Input Array is Checked to the Given Output 
	for(j=0;j<testDB[i].length;j++)
		if(testDB[i].input[j]!=testDB[i].output[j])
			return 0;
	return 1;
}
int main()
{
	int j,i;
	for(i=0;i<10;i++)
	{
		fix(testDB[i].input,testDB[i].length);
		if(isCheck(i))
			printf("Valid\n");
		else
			printf("Invalid\n");
	}
	return 0;
}