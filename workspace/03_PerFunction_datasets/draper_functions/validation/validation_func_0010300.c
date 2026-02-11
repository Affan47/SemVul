InstallStrategy(char *alias,char *classes)

{ struct Strategy *ptr;
  char ebuff[CF_EXPANDSIZE];

 Debug1("InstallStrategy(%s,%s)\n",alias,classes);

 if (! IsInstallable(classes))
    {
    Debug1("Not installing Strategy no match\n");
    return;
    }

 ExpandVarstring(alias,ebuff,"");

 if ((ptr = (struct Strategy *)malloc(sizeof(struct Strategy))) == NULL)
    {
    FatalError("Memory Allocation failed for InstallStrategy() #1");
    }

 if ((ptr->name = strdup(ebuff)) == NULL)
    {
    FatalError("Memory Allocation failed in InstallStrategy");
    }

 ExpandVarstring(classes,ebuff,"");

 if ((ptr->classes = strdup(ebuff)) == NULL)
    {
    FatalError("Memory Allocation failed in InstallStrategy");
    }

 if (VSTRATEGYLISTTOP == NULL)
    {
    VSTRATEGYLIST = ptr;
    }
 else
    {
    VSTRATEGYLISTTOP->next = ptr;
    }

 ptr->next = NULL;
 ptr->type = 'r';
 ptr->done = 'n';
 ptr->strategies = NULL;

 VSTRATEGYLISTTOP = ptr;
}
