HandleVarSet(char const * const str)
{
    if (str[0] != '@') return;
    char name[STR_LEN+1], value[STR_LEN+1];
    str_splitstrat(str+1,name,'=',value);
    str_cutat(name,' ');
    setVar(name, str_skipspace(value));
}
