ecore_ipc_server_del(Ecore_Ipc_Server *svr)
{
   void *data;

   if (!ECORE_MAGIC_CHECK(svr, ECORE_MAGIC_IPC_SERVER))
     {
        ECORE_MAGIC_FAIL(svr, ECORE_MAGIC_IPC_SERVER,
                         "ecore_ipc_server_del");
        return NULL;
     }
   if (svr->delete_me) return NULL;

   data = svr->data;
   svr->data = NULL;
   svr->delete_me = 1;
   if (svr->event_count == 0)
     {
        Ecore_Ipc_Client *cl;

        EINA_LIST_FREE(svr->clients, cl)
          ecore_ipc_client_del(cl);
        if (svr->server) ecore_con_server_del(svr->server);
        servers = eina_list_remove(servers, svr);

        if (svr->buf) free(svr->buf);
        ECORE_MAGIC_SET(svr, ECORE_MAGIC_NONE);
        free(svr);
     }
   return data;
}
