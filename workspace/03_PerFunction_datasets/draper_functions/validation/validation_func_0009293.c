_cpufreq_menu_restore_governor(void *data __UNUSED__, E_Menu *m __UNUSED__, E_Menu_Item *mi)
{
   cpufreq_config->restore_governor = e_menu_item_toggle_get(mi);
   if ((!cpufreq_config->governor) ||
       (strcmp(cpufreq_config->status->cur_governor, cpufreq_config->governor)))
     {
        eina_stringshare_replace(&cpufreq_config->governor,
                                 cpufreq_config->status->cur_governor);
     }
   e_config_save_queue();
}
