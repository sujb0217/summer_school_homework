#include <iostream>
#include <unistd.h>
using namespace std;

void progressBar() {
    cout << "* Loading" << '\n';
    sleep(2);
    cout << "###############    " << "(1/2)" << '\n';
    sleep(1);
    cout << "###############    " << "(2/2)";
}