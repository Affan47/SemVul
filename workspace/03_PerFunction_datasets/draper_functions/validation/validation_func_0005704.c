localstartid ( ptlocon, name1, name2)

locon_list *ptlocon;
char *name1, *name2;


{

 if ( (name1 == NULL) || (name2 == NULL) )
    fatalerror ("Invalid connector name. (localstartid)");

 name1 = namealloc (name1);
 name2 = namealloc (name2);
 if (name1 == name2) return;
 for (; ptlocon != NULL; ptlocon = ptlocon->NEXT)
     if (ptlocon->NAME == name2) ptlocon->NAME = name1;
}
