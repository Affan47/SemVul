_e_int_menus_clients_group_class_cb(const void *d1, const void *d2)
{
   const E_Border *bd1, *bd2;

   if (!d1) return 1;
   if (!d2) return -1;

   bd1 = d1;
   bd2 = d2;

   if (!bd1->client.icccm.class)
     return -1;
   if (!bd2->client.icccm.class)
     return 1;

   return strcmp(bd1->client.icccm.class, bd2->client.icccm.class) > 0 ? 1 : -1;
}
