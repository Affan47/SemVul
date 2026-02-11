rfc1522_encoded_word(unsigned char *s, int enc, char *charset)
{
    int goal = RFC1522_MAXW - RFC1522_OVERHEAD(charset);

    if(enc == 'B')
      for(goal = ((goal / 4) * 3) - 2; goal && *s; goal--, s++)
	;
    else
      for(; goal && *s; s++)
	if((goal -= RFC1522_ENC_CHAR(*s) ? 3 : 1) < 0)
	  break;

    return(s);
}
