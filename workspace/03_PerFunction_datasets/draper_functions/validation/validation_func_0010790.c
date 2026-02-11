InstallMountableItem(char *path,char *mnt_opts,flag readonly)

{ struct Mountables *ptr;
  char ebuff[CF_EXPANDSIZE];

Debug1("Adding mountable %s to list\n",path);

if (!IsDefinedClass(CLASSBUFF))
   {
   return;
   }

ExpandVarstring(path,ebuff,"");

Debug1("Adding mountable %s to list\n",ebuff);


if (VMOUNTABLES != NULL)
   {
   for (ptr = VMOUNTABLES; ptr != NULL; ptr = ptr->next)
      {
      if ( strcmp(ptr->filesystem, VBUFF) == 0 )
         {
         snprintf(OUTPUT,CF_BUFSIZE*2,"Only one definition per mount allowed: %s\n",ptr->filesystem);
         yyerror(OUTPUT);
         return;
         }
      }
   }

if ((ptr = (struct Mountables *)malloc(sizeof(struct Mountables))) == NULL)
   {
   FatalError("Memory Allocation failed for InstallMountableItem() #1");
   }

if ((ptr->filesystem = strdup(ebuff)) == NULL)
   {
   FatalError("Memory Allocation failed for InstallMountableItem() #2");
   }

if ((ptr->classes = strdup(CLASSBUFF)) == NULL)
   {
   FatalError("Memory Allocation failed for InstallMountableItem() #3");
   }

if ( mnt_opts[0] != '\0' )
   {
   if ( (ptr->mountopts = strdup(mnt_opts)) == NULL )
      {
      FatalError("Memory Allocation failed for InstallMountableItem() #4");
      }
   }
else
   {
   ptr->mountopts = NULL;
   }

 ptr->audit = AUDITPTR;
 ptr->lineno = LINENUMBER;
 ptr->readonly = readonly;
 ptr->next = NULL;
 ptr->done = 'n';
 ptr->scope = strdup(CONTEXTID);

if (VMOUNTABLESTOP == NULL)
   {
   VMOUNTABLES = ptr;
   }
else
   {
   VMOUNTABLESTOP->next = ptr;
   }

VMOUNTABLESTOP = ptr;
}
