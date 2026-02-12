static char* getToken(char** str, const char* delims) {
    char* token;

    if (*str==NULL) {

        return NULL;
    }

    token=*str;
    while (**str!='\0') {
        if (strchr(delims,**str)!=NULL) {
            **str='\0';
            (*str)++;
            return token;
        }
        (*str)++;
    }

    *str=NULL;
    return token;
}
