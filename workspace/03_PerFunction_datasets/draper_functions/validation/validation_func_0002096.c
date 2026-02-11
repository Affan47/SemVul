e_border_icon_add(E_Border *bd,
                  Evas *evas)
{
   Evas_Object *o;

   E_OBJECT_CHECK_RETURN(bd, NULL);
   E_OBJECT_TYPE_CHECK_RETURN(bd, E_BORDER_TYPE, NULL);

   o = NULL;
   if (bd->internal)
     {
        if (!bd->internal_icon)
          {
             o = e_icon_add(evas);
             e_util_icon_theme_set(o, "enlightenment");
          }
        else
          {
             if (!bd->internal_icon_key)
               {
                  char *ext;

                  ext = strrchr(bd->internal_icon, '.');
                  if ((ext) && ((!strcmp(ext, ".edj"))))
                    {
                       o = edje_object_add(evas);
                       if (!edje_object_file_set(o, bd->internal_icon, "icon"))
                         e_util_icon_theme_set(o, "enlightenment");
                    }
                  else if (ext)
                    {
                       o = e_icon_add(evas);
                       e_icon_file_set(o, bd->internal_icon);
                    }
                  else
                    {
                       o = e_icon_add(evas);
                       if (!e_util_icon_theme_set(o, bd->internal_icon))
                         e_util_icon_theme_set(o, "enlightenment");
                    }
               }
             else
               {
                  o = edje_object_add(evas);
                  edje_object_file_set(o, bd->internal_icon,
                                       bd->internal_icon_key);
               }
          }
        return o;
     }
   if ((e_config->use_app_icon) && (bd->icon_preference != E_ICON_PREF_USER))
     {
        if (bd->client.netwm.icons)
          {
             o = e_icon_add(evas);
             e_icon_data_set(o, bd->client.netwm.icons[0].data,
                             bd->client.netwm.icons[0].width,
                             bd->client.netwm.icons[0].height);
             e_icon_alpha_set(o, 1);
             return o;
          }
     }
   if (!o)
     {
        if ((bd->desktop) && (bd->icon_preference != E_ICON_PREF_NETWM))
          {
             o = e_icon_add(evas);
             if (o)
               {
                  e_icon_fdo_icon_set(o, bd->desktop->icon);
                  return o;
               }
          }
        else if (bd->client.netwm.icons)
          {
             o = e_icon_add(evas);
             e_icon_data_set(o, bd->client.netwm.icons[0].data,
                             bd->client.netwm.icons[0].width,
                             bd->client.netwm.icons[0].height);
             e_icon_alpha_set(o, 1);
             return o;
          }
     }

   o = e_icon_add(evas);
   e_util_icon_theme_set(o, "unknown");
   return o;
}
