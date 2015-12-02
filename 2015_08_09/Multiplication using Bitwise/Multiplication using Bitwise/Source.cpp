#include<stdio.h>
struct test
{
	int a;
	int b;
	int answer;
}testDB[10]={
	{3,2,6},//Both the Numbers are Positive
	{13,2,26},
	{31,12,372},
	{3,2,6},
	{-3,2,-6},//For Negative Numbers
	{3,12,36},
	{3.14,2,6.28},//Floats
	{-13,2,-26},
	{3,-2,-6},
	{-3,-2,6}
};
int add(int x, int y)
{
    // Iterate till there is no carry  
    while (y != 0)
    {
        // carry now contains common set bits of x and y
        int carry = x & y;  

        // Sum of bits of x and y where at least one of the bits is not set
        x = x ^ y; 

        // Carry is shifted by one so that adding it to x gives the required sum
        y = carry << 1;
    }
    return x;
}
int multiply(int a,int b)
{
	if(b<0)
	{
		a*=-1;
		b*=-1;
	}
	int result=0;
	while(b != 0)               // Iterate the loop till b==0
    {
		 if (b&01)                // Bitwise &  of the value of b with 01	
	        {
	          result=add(result,a);     // Add a to result if b is odd .
	        }
	      a<<=1;                   // Left shifting the value contained in 'a' by 1 
	                               // multiplies a by 2 for each loop
	      b>>=1;                   // Right shifting the value contained in 'b' by 1.
	 }
	return result;
}
int compare(int i,int ans)
{
	if(testDB[i].answer==ans)
		return 1;
	else 
		return 0;
}
int main()
{
	int i;
	for(i=0;i<10;i++)
	{
		int ans=multiply(testDB[i].a,testDB[i].b);
		if(compare(i,ans))
			printf("Valid\n");
		else
			printf("Invalid\n");
	}
	return 0;
}