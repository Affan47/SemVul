_e_module_free(E_Module *m)
{
   E_Config_Module *em;
   Eina_List *l;

   EINA_LIST_FOREACH(e_config->modules, l, em)
     {
        if (!em) continue;
        if (!e_util_strcmp(em->name, m->name))
          {
             e_config->modules = eina_list_remove(e_config->modules, em);
             if (em->name) eina_stringshare_del(em->name);
             E_FREE(em);
             break;
          }
     }

   if ((m->enabled) && (!m->error))
     {
        m->func.save(m);
        m->func.shutdown(m);
     }
   if (m->name) eina_stringshare_del(m->name);
   if (m->dir) eina_stringshare_del(m->dir);

   _e_modules = eina_list_remove(_e_modules, m);
   free(m);
}
