_ds_shutdown(Dropshadow *ds)
{
   free(ds->conf);
   E_CONFIG_DD_FREE(ds->conf_edd);
   while (ds->cons)
     {
        E_Container *con;

        con = ds->cons->data;
        ds->cons = eina_list_remove_list(ds->cons, ds->cons);
        e_container_shape_change_callback_del(con, _ds_shape_change, ds);
     }
   while (ds->shadows)
     {
        Shadow *sh;

        sh = ds->shadows->data;
        _ds_shadow_del(sh);
     }
   if (ds->idler_before) e_main_idler_before_del(ds->idler_before);
   free(ds->table.gauss);
   free(ds->table.gauss2);
   _ds_shared_free(ds);
   free(ds);
}
