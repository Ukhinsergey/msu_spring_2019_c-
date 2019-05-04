#include <iostream>
#include <string>
#include <fstream>
#include <thread>

 using namespace std;

const char* input_file = "input.bin";
const char* output_file = "output.bin";
using uint = unsigned int;

 int get_file_size(string filename)
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}

 void mergefile(const string &sort_file1, const string &sort_file2, const string &my_out_sort_file) {
    FILE* out = fopen(my_out_sort_file.c_str(), "wb");

     uint64_t sort1_size = get_file_size(sort_file1) / sizeof(uint64_t);
    FILE* sort1 = fopen(sort_file1.c_str(), "rb");

     uint64_t sort2_size = get_file_size(sort_file2) / sizeof(uint64_t);
    FILE* sort2 = fopen(sort_file2.c_str(), "rb");

     uint64_t temp1, temp2;
    fread(&temp1, sizeof(temp1), 1, sort1);
    fread(&temp2, sizeof(temp2), 1, sort2);
    while(sort1_size != 0 || sort2_size != 0) {
        if (sort1_size == 0) {
            while(sort2_size != 0) {
                fwrite(&temp2, sizeof(temp2), 1, out);
                --sort2_size;
                if( sort2_size > 0 ) {
                    fread(&temp2, sizeof(temp2), 1, sort2);
                }
            }
        } else if (sort2_size == 0) {
            while(sort1_size != 0) {
                fwrite(&temp1, sizeof(temp1), 1, out);
                --sort1_size;
                if( sort1_size > 0 ) {
                    fread(&temp1, sizeof(temp1), 1, sort1);
                }
            }
        } else if(temp1 <= temp2) {
            fwrite(&temp1, sizeof(temp1), 1, out);
            --sort1_size;
            if( sort1_size > 0 ) {
                fread(&temp1, sizeof(temp1), 1, sort1);
            }
        } else {
            fwrite(&temp2, sizeof(temp2), 1, out);
            --sort2_size;
            if( sort2_size > 0 ) {
                fread(&temp2, sizeof(temp2), 1, sort2);
            }
        }
    }
    fclose(sort1);
    fclose(sort2);
    fclose(out);
}


 //return file name
string mergesort(uint64_t left, uint64_t right, uint depth) {
    if (left == right) {
        string my_out_sort_file = string(to_string(left) + '-' + to_string(right) + '-' + to_string(depth));
        FILE* out = fopen(my_out_sort_file.c_str(), "wb");
        FILE* in = fopen(input_file, "rb");
        fseek(in, sizeof(uint64_t) * left, SEEK_SET);
        uint64_t temp;
        fread(&temp, sizeof(temp), 1, in);
        fwrite(&temp, sizeof(temp), 1, out);
        fclose(in);
        fclose(out);

         return my_out_sort_file;
    }

     uint64_t middle = (left + right) / 2;
    string sort_file1;
    string sort_file2;
    sort_file1 = mergesort(left, middle, depth + 1);
    sort_file2 = mergesort(middle + 1, right, depth + 1);

     string my_out_sort_file = string(to_string(left) + '-' + to_string(right) + '-' + to_string(depth));
    mergefile(sort_file1, sort_file2, my_out_sort_file);

     return my_out_sort_file;
}



 int main(int argc, char **argv)
{
    if (argc != 3) {
        cout << "2 args: (1 - random || 2 - input.bin) && sizeofarray(for random)" << endl;
        return 0;
    }
    int random;
    int size;
    sscanf(argv[1], "%d", &random);
    sscanf(argv[2], "%d", &size);

     if(random == 1) {
        FILE* in = fopen(input_file, "wb"); 
        srand(time(NULL)); 
        // generate input 
        for (int i = 0; i < size; i++) {
            uint64_t temp = rand() % 100; 
            fwrite(&temp, sizeof(temp), 1, in); 
        } 
        fclose(in); 
    }
    uint64_t nums = get_file_size(input_file) / sizeof(uint64_t);

     thread t1(mergesort, 0, (nums - 1) / 2, 0);
    thread t2(mergesort, (nums - 1) / 2 + 1, nums - 1, 0);
    t1.join();
    t2.join();
    string str1 = string(to_string(0) + '-' + to_string((nums - 1) / 2) + '-' + to_string(0));
    string str2 = string(to_string((nums - 1) / 2 + 1) + '-' + to_string(nums - 1) + '-' + to_string(0));
    mergefile(str1, str2, output_file);
    return 0;
} 