
#include <iostream>
#include <cstring>

class Matrix {
    const size_t rows;
    const size_t columns;
    const unsigned long long size;
    int *data;

    class Proxy{
        int *row;
        size_t columns;
    public:
        Proxy(int *r, size_t columns): row(r), columns(columns){};
        int& operator[](size_t col) {
            if(col >= columns) {
                throw std::out_of_range("");
            }
            return  row[col];
        }
        const int& operator[](size_t col) const{
            if(col >= columns) {
                throw std::out_of_range("");
            }
            return row[col];
        }
    };

public:
    Matrix(size_t rows, size_t columns): rows(rows), columns(columns), size(rows * columns), data(nullptr){
        data = new int[size]();   
    } 
    
    Matrix(const Matrix &a): rows(a.rows), columns(a.columns), size(rows * columns), data(nullptr) {
        data = new int[size];
        memcpy(data, a.data, size * sizeof(int));
    }
    
    ~Matrix() {
        delete[] data;
    }

    int getRows(){
        return rows;
    }

    int getColumns(){
        return columns;
    }

    Matrix& operator *=(int n) {
        for(int i = 0 ; i < rows; ++i) {
            for(int j = 0 ; j < columns; ++j) {
                (*this)[i][j] *= n;
            }
        }
        return *this;
    }

    bool operator==(const Matrix &a) const{
        if (this == &a) {
            return true;
        }
        if (columns != a.columns) {
            return false;
        }
        if (rows != a.rows) {
            return false;
        }
        for(int i = 0 ; i < size; ++i) {
            if(data[i] != a.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix &a) const {
        return !(*this == a);
    }

    Proxy operator[](int r) {
        if (r >= rows) {
            throw std::out_of_range("");
        }
        return Proxy(data + columns * r, columns);
    }

    const Proxy operator[](int r) const{
        if (r >= rows) {
            throw std::out_of_range("");
        }
        return Proxy(data + columns * r, columns);
    }

};