#include <iostream>
#include <cmath>
#include <vector>
#include "numbers.dat"

int * genprime(int end, int &sizeprime) {
	int size = (int) sqrt(end + 1.0);
	int *prime = new int[size + 1];
	int *answ = new int[size + 1];
	for (int i = 0 ; i < size + 1; ++i) {
		prime[i] = 1;
	}
	prime[0] = prime[1] = 0;
	int k = 0;
	int temp;
	for(temp = 2; temp * temp <= end; ++temp) {
    	if (prime[temp]) {
    		answ[k] = temp;
    		++k;
        	for(long long  j = temp * temp; j * j <= end; j += temp ) {
                prime[j] = false;
            }
        }
    }
    sizeprime = k;
    delete []prime;
    return answ;
}



bool isprime(int number, int *primes, int sizeprime) {
	if (number == 1) {
		return false;
	}
	int end = (int) sqrt(number + 1.0);
	for(int i = 0; i < sizeprime; ++i) {
		if (number == primes[i]) {
			return true;
		} else if (number % primes[i]  == 0) {
			return false;
		}
	}
	return true;
}


int startindex(const int * data, int n, int num, int start, int end) {
	while(1) {
		int temp = end + start / 2;
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
	while(1) {
		int temp = end + start / 2;
		if (num == data[temp] && (temp == end || data[temp + 1] != num)) {
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


int main(int argc, char **argv) {
	if(argc % 2 == 0 || argc == 1) {
		return -1;
	}
	for (int i = 1; i < argc; i += 2)
    {
        int begin = std::atoi(argv[i]);
        int end = std::atoi(argv[i + 1]);
        int sizeprime;
        int  *primes = genprime(end, sizeprime);
        int ind1 = startindex(Data, Size, begin, 0, Size);
        int ind2 = endindex(Data, Size, end, 0, Size);

        if (ind1 == -1 || ind2 == -1) {
        	std::cout << 0 << std::endl;
        	continue;
        }
        int counter = 0;
        for (int i = ind1; i <= ind2; ++i) {
        	if (isprime(Data[i], primes, sizeprime)) {
        		++counter;
        	}
        }
        std::cout << counter << std::endl;
        delete[] primes;
    }

	return 0;
}


