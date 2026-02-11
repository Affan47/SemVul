printeno(int eno, const char* func)
{
    printf("Error: '%s(%d)' %s \n", strerror(eno), eno, func == NULL ? "" : func);
}
