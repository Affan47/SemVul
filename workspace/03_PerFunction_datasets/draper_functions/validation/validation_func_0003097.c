_init_done_cb(void *data, Eio_File *handler)
{
   E_Config_Dialog_Data *cfdata = data;
   if (cfdata->init[0] == handler)
     cfdata->init[0] = NULL;
   else
     cfdata->init[1] = NULL;
   if (cfdata->free) _free_data(NULL, cfdata);
}
