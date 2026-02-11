e_modapi_init(E_Module *m)
{
   Mod *mod;
   char buf[4096];

   mod = calloc(1, sizeof(Mod));
   m->data = mod;

   mod->module = m;
   snprintf(buf, sizeof(buf), "%s/e-module-comp.edj", e_module_dir_get(m));
   e_configure_registry_category_add("appearance", 10, _("Look"), NULL,
                                     "preferences-look");
   e_configure_registry_item_add("appearance/comp", 120, _("Composite"), NULL,
                                 buf, e_int_config_comp_module);

   e_mod_comp_cfdata_edd_init(&(mod->conf_edd),
                              &(mod->conf_match_edd));

   mod->conf = e_config_domain_load("module.comp", mod->conf_edd);
   if (mod->conf)
     {
        mod->conf->max_unmapped_pixels = 32 * 1024;
        mod->conf->keep_unmapped = 1;
     }
   else _e_mod_config_new(m);


   mod->conf->lock_fps = 0;
   mod->conf->indirect = 0;

   if (!e_config->use_composite)
     {
        e_config->use_composite = 1;
        e_config_save_queue();
     }


   {
      E_Module *m2;

      m2 = e_module_find("dropshadow");
      if (m2 && m2->enabled)
        {
           e_util_dialog_internal(_("Composite"),
                                  _("Dropshadow module is incompatible<br>"
                                    "with compositing. Disabling the<br>"
                                    "Dropshadow module."));
           e_module_disable(m2);
        }
   }


   if (mod->conf->first_draw_delay == 0)
     mod->conf->first_draw_delay = 0.20;

   _comp_mod = mod;

   if (!e_mod_comp_init())
     {

     }

   e_module_delayed_set(m, 0);
   e_module_priority_set(m, -1000);
   return mod;
}
