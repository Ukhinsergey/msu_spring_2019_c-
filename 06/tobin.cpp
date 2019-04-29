#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << " format: in.txt in.bin";
        return 0;
    }
    fstream fin(argv[1]);
    fstream fout(argv[2], ios::out | ios::binary | ios::trunc);
    uint64_t temp;
    while(fin >> temp) {
        fout.write(reinterpret_cast<char *> (&temp), sizeof(uint64_t));
    }
    fin.close();
    fout.close();
    return 0;
}

