schedd_order_destroy(void) {
   bool ret = true;

   DENTER(TOP_LAYER, "schedd_order_initialize");
   ret &= sge_sl_destroy(&Master_Request_Queue.request_list, NULL);
   DRETURN(ret);
}
