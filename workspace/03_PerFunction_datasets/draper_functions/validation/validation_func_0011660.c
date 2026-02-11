_e_configure_item_cb(void *data)
{
   E_Configure_Item *ci;
   E_Configure_CB *cb;

   if (!(ci = data)) return;
   cb = ci->cb;
   if (cb->path) e_configure_registry_call(cb->path, cb->eco->con, NULL);
}
