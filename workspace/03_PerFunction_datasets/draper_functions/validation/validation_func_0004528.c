FilterNameRegexMatch(char *filename,char *crit)

{ regex_t rx;
  regmatch_t pmatch;

if (CfRegcomp(&rx,crit,REG_EXTENDED) != 0)
   {
   return false;
   }

if (regexec(&rx,filename,1,&pmatch,0) == 0)
   {
   if ((pmatch.rm_so == 0) && (pmatch.rm_eo == strlen(filename)))
      {
      regfree(&rx);
      return true;
      }
  }

regfree(&rx);
return false;
}
