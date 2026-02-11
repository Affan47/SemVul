rem_lead_0chars(char *s)
{
 register int32 i, j;
 int32 slen;


 for (i = 0; ; i++)
  {

   if (s[i] == '\0') { s[0] = '0'; s[1] = '\0'; return; }
   if (s[i] != '0') break;
  }
 if (i == 0) return;

 if (s[i] == '.') i--;


 slen = strlen(s);
 for (j = 0; j < slen - i; j++) s[j] = s[i + j];
 s[slen - i] = '\0';
}
