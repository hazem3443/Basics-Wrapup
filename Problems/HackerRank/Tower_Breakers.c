#include <stdio.h>

int towerBreakers(int n, int m);

int ismove_intower(int x);

void main()
{

    // printf("towerBreakers test case 1 :%i\n", ismove_intower(7));

    // printf("towerBreakers test case 1 :%i\n", towerBreakers(2, 6)); // 2
    // printf("towerBreakers test case 1 :%i\n", towerBreakers(2, 2)); // 2
    // printf("towerBreakers test case 1 :%i\n", towerBreakers(1, 4)); // 1

    printf("towerBreakers test case 1 :%i\n", towerBreakers(1, 7)); // 1
    printf("towerBreakers test case 1 :%i\n", towerBreakers(3, 7)); // 1

    printf("towerBreakers test case 1 :%i\n", towerBreakers(2, 2)); // 2
    printf("towerBreakers test case 1 :%i\n", towerBreakers(1, 4)); // 1
}

int towerBreakers(int n, int m)
{
    int towers[n];
    for (int i = 0; i < n; i++)
        towers[i] = m;

    int turn = 0;
    for (int i = 0; i < n; i++)
    {
        while (ismove_intower(towers[i]))
        {
            // printf(">> :%i\n", turn);
            // printf("    >> :%i\n", towers[i]);
            towers[i] -= ismove_intower(towers[i]);
            turn++;
        }
    }
    if (turn % 2)
        return 1;
    else
        return 2;
}

int ismove_intower(int x)
{
    if (x == 1)
        return 0;

    int it = 1;
    if (it != 0)
        while (x % it)
            it++;
    return x - it;
}