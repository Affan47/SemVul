expression() {
        int result;
        if (isaddop(lookahead)) result = 0;
        else result = term();
        while (isaddop(lookahead)) {
                get_operator();
                if (value == "+") result += term();
                else if (value == "-") result -= term();
        }
        return result;
}
