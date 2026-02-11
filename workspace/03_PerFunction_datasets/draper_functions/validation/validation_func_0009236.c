_e_gadman_client_remove(void *data __UNUSED__, E_Gadcon_Client *gcc)
{
   if (gcc->cf)
     gcc->gadcon->cf->clients = eina_list_remove(gcc->gadcon->cf->clients, gcc->cf);
   e_object_del(E_OBJECT(gcc));
}
