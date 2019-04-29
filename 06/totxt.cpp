#include <fstream>
#include <complex>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << " format : input.bin output.txt " << endl;
        return 0;
    }

    fstream fin(argv[1], ios::in | ios::binary);
    fstream fout(argv[2], ios::out | ios::trunc);
    
    uint64_t temp;
    while(fin.read(reinterpret_cast<char *> (&temp), sizeof(temp))) {
        fout << temp << ' ';
    }
    
    fout.close();
    fin.close();
    return 0;
}
