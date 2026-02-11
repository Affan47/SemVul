e_exehist_newest_run_get(const char *exe)
{
   Eina_List *l;
   E_Exehist_Item *ei;
   const char *normal;

   _e_exehist_load();
   if (!_e_exehist) return 0.0;
   normal = _e_exehist_normalize_exe(exe);
   if (!normal) return 0.0;
   EINA_LIST_REVERSE_FOREACH(_e_exehist->history, l, ei)
     {
        if ((ei->normalized_exe) && (!strcmp(normal, ei->normalized_exe)))
          {
             eina_stringshare_del(normal);
             _e_exehist_unload_queue();
             return ei->exetime;
          }
     }
   eina_stringshare_del(normal);
   _e_exehist_unload_queue();
   return 0.0;
}
