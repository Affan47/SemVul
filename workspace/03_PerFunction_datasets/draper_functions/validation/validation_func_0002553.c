macke_origin(key, line, fp)
     char *key, *line;
     FILE_BUFFER    fp;
{
    int   index, indj, seqnum;
    char *eof, name[TOKENNUM], seq[LINENUM];


    data.seq_length=0;


    index=macke_abbrev(line, name, 0);
    eof=line;
    for(; eof!=NULL&&Cmpstr(key, name)==EQ; ){
        sscanf(line+index, "%d%s", &seqnum, seq);
        for(indj=data.seq_length; indj<seqnum; indj++)
            if(indj<data.max)
                data.sequence[data.seq_length++]
                    = '.';
            else    {
                data.max += 100;
                data.sequence = (char*)Reallocspace
                    (data.sequence, (unsigned)
                     (sizeof(char)*data.max));
                data.sequence[data.seq_length++]
                    = '.';
            }
        for(indj=0; seq[indj]!='\n'&&seq[indj]!='\0'; indj++)
            if(data.seq_length<data.max)
                data.sequence[data.seq_length++]
                    = seq[indj];
            else    {
                data.max += 100;
                data.sequence = (char*)Reallocspace
                    (data.sequence, (unsigned)
                     (sizeof(char)*data.max));
                data.sequence[data.seq_length++]
                    = seq[indj];
            }
        data.sequence[data.seq_length] = '\0';
        eof=Fgetline(line, LINENUM, fp);
        if(eof!=NULL) index = macke_abbrev(line, name, 0);

    }

    return(eof);
}
