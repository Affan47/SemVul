write_dual_alpha(FILE *f, int doflip)


{
    int i,j,start;
    unsigned char code[MAXN+MAXE+4];
    unsigned char precode[MAXN+MAXE+1];
    size_t length;

    length=2+ne+(ne/2)-nv;
    compute_dual_code(precode);

    if (precode[0] >= 10)
    {
        code[0] = '0' + precode[0]/10;
        code[1] = '0' + precode[0]%10;
        code[2] = ' ';
        length += 3;
	start=3;
    }
    else
    {
        code[0] = '0' + precode[0];
        code[1] = ' ';
        length += 2;
	start=2;
    }

    for (i = 1, j=start; j < length; ++i, ++j)
        if (precode[i]==0) code[j]=',';
        else code[j]=precode[i]-1+'a';

    code[j-1]='\n';
    if (fwrite(code,sizeof(unsigned char),length,f) != length)
    {
        fprintf(stderr,">E %s: fwrite() failed\n",cmdname);
        perror(">E ");
        exit(1);
    }
    if (doflip)
      { compute_dual_code_mirror(precode);
        for (i = 1, j=start; j < length; ++i, ++j)
	    if (precode[i]==0) code[j]=',';
            else code[j]=precode[i]-1+'a';
        code[j-1]='\n';
        if (fwrite(code,sizeof(unsigned char),length,f) != length)
	  {
	    fprintf(stderr,">E %s: fwrite() failed\n",cmdname);
	    perror(">E ");
	    exit(1);
	  }
      }
}
