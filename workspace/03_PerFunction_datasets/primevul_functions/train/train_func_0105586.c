STATIC unsigned  int
S_regex_set_precedence(const U8 my_operator) {


    switch (my_operator) {
        case '!':
            return 5;
        case '&':
            return 4;
        case '^':
        case '|':
        case '+':
        case '-':
            return 3;
        case ')':
            return 2;
        case ']':
            return 1;
    }

    NOT_REACHED;
    return 0;
}
