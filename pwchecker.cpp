#include "pwchecker.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <regex>
using namespace std;

int pwcheck::checker(string pw) {
    regex uppers("[A-Z]");
    regex lowers("[a-z]");
    regex chars("[$&+,:;=?@#|'<>.-^*()%!]");
    if(regex_search(pw, uppers) && regex_search(pw, lowers) && regex_search(pw, chars) && pw.length() > 7) {
        return 0;
    }
    else { return 1; }
}
