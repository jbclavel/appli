#include <string>
#include <iostream>
#include "IO.h"
#include "PHIO.h"
#include "PH.h"

using name space std;

int main(int argc, char *argv[]) {
    string filename;
    cout << "Filename=";
    cin >> filename;
    PHPtr ph = PHIO::parseFile  (filename);
    PHIO::exportToPNG (ph, "output.png");
    return 0;
}
