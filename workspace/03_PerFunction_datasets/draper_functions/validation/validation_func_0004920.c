isdelim(char c) {
    return c == ',' || c == ':' || c == ']' || c == '}' || isspace(c) || !c;
}
