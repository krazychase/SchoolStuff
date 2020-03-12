// Chase Brown
// Sum Kind Of Problem
// 3/12/20

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

char* skop(bool test, int p, int k, int n)
{
    static char answer[400000];
    memset(answer, 0, 400000);
    if(test == false)
	    scanf("%d",&p);
	while (p-- > 0)
	{
        char temp[50];
        memset(temp, 0, 50);
        if(test == false)
		    scanf("%d %d",&k,&n);
        int n2 = n * n;
        sprintf(temp, "%d %d %d %d\n", k, (n2+n)/2, n*n, n2+n);
		strcat(answer, temp);
	}
    return answer;
}

void testSkop()
{
    assert(strcmp(skop(true, 1, 1, 1001), "1 501501 1002001 1003002\n") == 0);
    assert(strcmp(skop(true, 1, 1, 2112), "1 2231328 4460544 4462656\n") == 0);
    assert(strcmp(skop(true, 1, 1, 5), "1 15 25 30\n") == 0);
    printf("Tests passed");
}

int main(int argc, char** argv)
{
    if(argc > 1 && strcmp(argv[1], "test") == 0)
    {
        testSkop();
    }
    else
    {
        printf("%s", skop(false, 0, 0, 0));
    }
    return 0;
}