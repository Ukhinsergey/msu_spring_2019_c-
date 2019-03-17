#include <iostream>
#include <cmath>
#include "numbers.dat"


int *genprime(int end, size_t &sizeprime) {
    int *prime = new int[end + 1];
    for (int i = 0 ; i < end + 1; ++i) {
        prime[i] = 1;
    }
    prime[0] = prime[1] = 0;
    int temp = 0;
    for(temp = 2; temp <= end; ++temp) {
        if (prime[temp]) {
            for(long long  int j = (long long) temp * temp; j <= end; j += temp ) {
                prime[j] = 0;
            }
        }
    }
    sizeprime = end + 1;
    return prime;
}





int startindex(const int * data, int n, int num, int start, int end) {
    while(true) {
        int temp = (end + start) / 2;
        if (num == data[temp] && (temp == 0 || data[temp - 1] != num)) {
            return temp;
        }
        if (num <= data[temp]) {
            end = temp - 1;
        } else {
            start = temp + 1;
        }
        if (start > end) {
            return -1;
        }
    }
}



int endindex(const int * data, int n, int num, int start, int end) {
    while(true){
        int temp = (end + start) / 2;
        if ((num == data[temp]) && (temp == end || data[temp + 1] != num)) {
            return temp;
        }
        if (num < data[temp]) {
            end = temp - 1;
        } else {
            start = temp + 1;
        }
        if (start > end) {
            return -1;
        }
    }
}

using namespace std;
int main(int argc, char **argv) {
    if(argc % 2 == 0 || argc == 1) {
        return -1;
    }
    int counter = 0;
    for (int i = 1; i < argc; i += 2)
    {
        int begin = std::atoi(argv[i]);
        int end = std::atoi(argv[i + 1]);
        size_t sizeprime;
        int ind1 = startindex(Data, Size, begin, 0, Size);
        int ind2 = endindex(Data, Size, end, 0, Size);
        if ((ind1 == -1) || (ind2 == -1)) {
            std::cout << 0 << std::endl;
            continue;
        }
        int *primes = genprime(end, sizeprime);
        counter = 0;
        for (int i = ind1; i <= ind2; ++i) {
            if (primes[Data[i]]) {
                ++counter;
            }
        }
        std::cout << counter << std::endl;
        delete[] primes;
    }

    return 0;
}