#include <stdio.h>
#include "Nos_Fichiers/source/MenuUtils.h"

using namespace std;


int main()
{
    setlocale(LC_ALL,""); //So UTF-32 gets converted into UTF-8
    srand(time(NULL)); //For the random ghost AI
    MainMenu();

    return 0;
}
