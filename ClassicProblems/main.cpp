#include <iostream>
#include <iomanip>
using namespace std;
#include "CatalanNumber_Backtrack.h"

int main()
{
    vector<char> seq;

    backtrackCatalanSequence(1);

    cout << "--------------" << endl;

    CatalanNumber01Sequence(2,seq,0,0);

    //trainSequencing(3,seq,0,0);

    return 0;
}
