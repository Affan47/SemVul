_create_data(E_Config_Dialog *cfd)
{
   E_Config_Dialog_Data *cfdata;
   E_Config_Data *data;
   const char *ext;

   if (!(data = cfd->data)) return NULL;
   if (!data->filename) return NULL;
   if (!(ext = strrchr(data->filename, '.'))) return NULL;

   cfdata = E_NEW(E_Config_Dialog_Data, 1);
   cfdata->data = data;
   cfdata->apps_xdg.cfdata = cfdata;
   cfdata->apps_user.cfdata = cfdata;
   if (!strcmp(ext, ".menu"))
     cfdata->apps = _load_menu(data->filename);
   else if (!strcmp(ext, ".order"))
     cfdata->apps = _load_order(data->filename);

   return cfdata;
}
