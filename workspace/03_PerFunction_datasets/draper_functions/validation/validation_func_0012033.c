macke_continue_line(key, oldname, var, line, fp)
     const char *key;
     char       *oldname, **var, *line;
     FILE_BUFFER fp;
{
    char    *eof, name[TOKENNUM], newkey[TOKENNUM];
    int index;


    for(eof=Fgetline(line, LINENUM, fp);
        eof!=NULL; eof=Fgetline(line, LINENUM, fp)) {
        if(Lenstr(line)<=1) continue;

        index = macke_abbrev(line, name, 0);
        if(Cmpstr(name, oldname)!=EQ)   break;

        index = macke_abbrev(line, newkey, index);
        if(Cmpstr(newkey, key)!=EQ) break;

        Append_rp_eoln(var, line+index);
    }

    return(eof);
}
