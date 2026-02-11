CommPrefix(char *execstr,char *comm)

{ char *sp;

for (sp = execstr; *sp != ' ' && *sp != '\0'; sp++)
   {
   }

if (sp - 10 >= execstr)
   {
   sp -= 10;
   }
else
   {
   sp = execstr;
   }

memset(comm,0,20);
strncpy(comm,sp,15);
}
