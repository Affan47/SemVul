ecore_con_client_fd_get(Ecore_Con_Client *cl)
{
   if (!ECORE_MAGIC_CHECK(cl, ECORE_MAGIC_CON_CLIENT))
     {
        ECORE_MAGIC_FAIL(cl, ECORE_MAGIC_CON_CLIENT, __func__);
        return -1;
     }
   return ecore_main_fd_handler_fd_get(cl->fd_handler);
}
