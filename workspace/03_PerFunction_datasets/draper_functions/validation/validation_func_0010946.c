vm_platform_find_cli_name(char *name)
{
   struct vm_platform_list *p;

   for(p=vm_platforms;p;p=p->next)
      if (!strcmp(p->platform->cli_name,name))
         return(p->platform);

   return NULL;
}
