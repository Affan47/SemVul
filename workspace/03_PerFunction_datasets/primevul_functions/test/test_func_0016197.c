bool DL_Dxf::stripWhiteSpace(char** s, bool stripSpace) {

    int lastChar = strlen(*s) - 1;


    while ( (lastChar >= 0) &&
            (((*s)[lastChar] == 10) || ((*s)[lastChar] == 13) ||
             (stripSpace && ((*s)[lastChar] == ' ' || ((*s)[lastChar] == '\t')))) ) {
        (*s)[lastChar] = '\0';
        lastChar--;
    }


    if (stripSpace) {
        while ((*s)[0]==' ' || (*s)[0]=='\t') {
            ++(*s);
        }
    }

    return ((*s) ? true : false);
}
