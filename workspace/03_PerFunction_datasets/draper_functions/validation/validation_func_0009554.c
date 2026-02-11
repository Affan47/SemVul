CheckParseClass(char *lval,char *s,char *range)

{ char output[CF_BUFSIZE];

if (s == NULL)
   {
   return false;
   }

Debug("\nCheckParseClass(%s => %s/%s)\n",lval,s,range);

if (strlen(range) == 0)
   {
   return true;
   }

if (FullTextMatch(range,s))
   {
   return true;
   }

snprintf(output,CF_BUFSIZE,"Class item on rhs of lval \'%s\' given as { %s } is out of bounds (should match %s)",lval,s,range);
ReportError(output);
return false;
}
