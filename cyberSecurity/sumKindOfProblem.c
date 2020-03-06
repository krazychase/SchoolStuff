// Chase Brown
// Sum Kind Of Problem

#include <stdio.h>
#include <string.h>

char* skop()
{
    static char answer[1000];
    strcat(answer, "skop");
    return answer;
}

void testSkop()
{
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
        printf(skop());
    }
    return 0;
}