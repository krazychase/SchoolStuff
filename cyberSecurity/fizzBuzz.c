// Chase Brown
// FizzBuzz

#include <stdio.h>
#include <string.h>
#include <assert.h>

char* fizzBuzz(int x ,int y, int n)
{
    int i;
    static char answer[1000];
    memset(answer, 0, 1000);
    for (i = 1; i <= n; i++)
    {
		if (i % x == 0) 
        {
			if (i % y == 0) 
            {
				strcat(answer, "FizzBuzz\n");
			} 
            else 
            {
				strcat(answer, "Fizz\n");
			}
		} 
        else if (i % y == 0) 
        {
			strcat(answer, "Buzz\n");
		} 
        else 
        {
			char c[10];
            sprintf(c, "%d\n", i);    // turn int to char
            strcat(answer, c);
        }
    }
    return answer;
}

void testFizzBuzz()
{
    assert(strcmp(fizzBuzz(1, 1, 1), "FizzBuzz\n") == 0);
    assert(strcmp(fizzBuzz(2, 4, 8), "1\nFizz\n3\nFizzBuzz\n5\nFizz\n7\nFizzBuzz\n") == 0);
    assert(strcmp(fizzBuzz(15, 20, 10), "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n") == 0);
    printf("Tests passed");
}

int main(int argc, char** argv)
{
    if(argc > 1 && strcmp(argv[1], "test") == 0)
    {
        testFizzBuzz();
    }
    else
    {
        int x, y, n;
        scanf("%d %d %d", &x, &y, &n);
        printf("%s", fizzBuzz(x, y, n));
    }
    return 0;
}