append(const char* s1, const char* s2)
{
    int len = (s1?strlen(s1):0)+(s2?strlen(s2):0);
    char* result = (char*)emalloc(len+1);
    result[0] = '\0';
    if(s1) strcat(result,s1);
    if(s2) strcat(result,s2);
    return result;
}
