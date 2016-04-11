#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    const int dividend = 6;
    const int divisor  = 2;
    int result = dividend / divisor;
    result += 3;
    
    cout << result << endl;

    char stopChar;
    cout << "Press any key and \"Enter\" to continue" << endl;
    cin >> stopChar;
    
    return EXIT_SUCCESS;
}
