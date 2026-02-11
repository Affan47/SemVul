ttputc(UCS ucs)
{
    unsigned char obuf[MAX(MB_LEN_MAX,32)];
    int  r, i, width = 0, outchars = 0;
    int  ret = 0;

    if(ucs < 0x80)
      return(putchar((unsigned char) ucs));

    width = wcellwidth(ucs);

    if(width < 0){
	width = 1;
	obuf[outchars++] = '?';
    }
    else{


	outchars = wtomb((char *) obuf, ucs);
	if(outchars < 0){
	    width = 1;
	    obuf[0] = '?';
	    outchars = 1;
	}
    }

    for(i = 0; i < outchars; i++){
	r = putchar(obuf[i]);
	ret = (ret == EOF) ? EOF : r;
    }

    return(ret);
}
