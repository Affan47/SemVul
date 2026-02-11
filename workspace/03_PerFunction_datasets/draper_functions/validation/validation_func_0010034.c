poolcat(const char* s1, const char* s2)
{
    int len1, len2;
    char* cat;
    if(s1 == NULL && s2 == NULL) return NULL;
    len1 = (s1?strlen(s1):0);
    len2 = (s2?strlen(s2):0);
    cat = poolalloc(len1+len2+1);
    cat[0] = '\0';
    if(s1 != NULL) strcat(cat,s1);
    if(s2 != NULL) strcat(cat,s2);
    return cat;
}
