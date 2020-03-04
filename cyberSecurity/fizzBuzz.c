// Chase Brown
// FizzBuzz

#include <stdio.h>

void fizzBuzz(x ,y, n)
{
    int i;
    for (i = 1; i <= n; i++)
    {
		if (i % x == 0) 
        {
			if (i % y == 0) 
            {
				printf("FizzBuzz\n");
			} 
            else 
            {
				printf("Fizz\n");
			}
		} 
        else if (i % y == 0) 
        {
			printf("Buzz\n");
		} 
        else 
        {
			printf("%d\n", i);
        }
    }
}

void testFizzBuzz()
{
    
}

int main(int argc, char** argv)
{
    if(argc < 1 && argv[1] == "test")
    {
        testFizzBuzz();
    }
    else
    {
        int x, y, n;
        scanf("%d %d %d", &x, &y, &n);
        fizzBuzz(x, y, n);
    }
    system("pause");
    return 0;
}