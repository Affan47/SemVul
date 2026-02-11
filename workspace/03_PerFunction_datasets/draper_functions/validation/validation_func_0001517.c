gwy_app_data_browser_get_data_ids_wrap(GwyContainer *data)
{
   gint *ids, *id_p, c = 0;

   ids = gwy_app_data_browser_get_data_ids(data);
   id_p = ids;
   while (*(id_p++) != -1)
      c++;

   return create_array(ids, c, sizeof(gint), TRUE);
}
