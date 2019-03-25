#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct Result{
    int64_t res;
    string expr;
    Result(string &expr, int64_t res) : res(res), expr(expr){};
};


Result add_sub(string &expr);
Result mul_div(string &expr);
Result num(string &expr);

int64_t parse(const string &expr1) {
    //remove spaces
    string expr = expr1;
    for(auto i = expr.end() -1 ; i >= expr.begin(); --i) {
        if(*i == ' ') {
            expr.erase(i);
        }
    }
  
    Result res = add_sub(expr);
    if (!res.expr.empty()) {
        throw std::invalid_argument("error(not parse to the end) at: " + res.expr);
    } else {
        return res.res;
    }
}

Result add_sub(string &expr) {
    Result cur = mul_div(expr);
    int64_t res = cur.res;
    while(true) {
        if(cur.expr.length() == 0) {
            return cur;
        }
        char sign = cur.expr[0];
        if(sign != '+' && sign != '-') {
            return cur;
        }
        cur.expr.erase(0,1);
        Result next = mul_div(cur.expr);
        if (sign == '+') {
            res = res + next.res;
        } else {
            res = res - next.res;
        }
        cur = Result(next.expr, res);

    }
    return cur;
}

Result mul_div(string &expr) {
    Result cur = num(expr);
    int64_t res = cur.res;
    while(true) {
        if(cur.expr.length() == 0) {
            return cur;
        }
        char sign = cur.expr[0];
        if(sign != '*' && sign != '/') {
            return cur;
        }
        cur.expr.erase(0,1);
        Result next = num(cur.expr);
        if (sign == '*') {
            res = res * next.res;
        } else {
            if (next.res == 0) {
                throw std::invalid_argument("error(division by zero)");
            }
            res = res / next.res;
        }
        cur = Result(next.expr, res);

    }
    return cur;
}

Result num(string &expr) {
    int i = 0;
    bool negative = false;
    while(expr[i] == '-') {
        negative = !negative;
        ++i;
    }
    expr.erase(0,i);
    i = 0;
    while(i < expr.length() && isdigit(expr[i])) {
        ++i;
    }
    if (i == 0) {
        throw std::invalid_argument("error(not number) at: " + expr);
    }
    int64_t temp = stoll(expr);
    if(negative) {
        temp = -temp;
    }
    expr.erase(0,i);
    return Result(expr, temp);
}


int main(int argc, char **argv) {
    if(argc != 2) {
        cout << "error" << endl;
        return 1;
    }
    string expr(argv[1]);
    try {
        cout << parse(expr) << endl;
    } 
    catch (const std::invalid_argument& ia) {
        cout << "error " << endl;
        //cerr << ia.what();
        return 1;
    }
    return 0;
}