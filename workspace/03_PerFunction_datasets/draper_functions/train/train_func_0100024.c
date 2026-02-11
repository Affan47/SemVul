cl_com_setup_connection(cl_com_handle_t* handle, cl_com_connection_t** connection) {
   int ret_val = CL_RETVAL_HANDLE_NOT_FOUND;
   if (handle != NULL) {
      switch(handle->framework) {
         case CL_CT_TCP: {
            ret_val = cl_com_tcp_setup_connection(connection,
                                                  handle->service_port,
                                                  handle->connect_port,
                                                  handle->data_flow_type,
                                                  handle->auto_close_mode,
                                                  handle->framework,
                                                  CL_CM_DF_BIN,
                                                  handle->tcp_connect_mode);
            break;
         }
         case CL_CT_SSL: {
            ret_val = cl_com_ssl_setup_connection(connection,
                                                  handle->service_port,
                                                  handle->connect_port,
                                                  handle->data_flow_type,
                                                  handle->auto_close_mode,
                                                  handle->framework,
                                                  CL_CM_DF_BIN,
                                                  handle->tcp_connect_mode,
                                                  handle->ssl_setup);
            break;
         }
         case CL_CT_UNDEFINED: {
            ret_val = CL_RETVAL_UNDEFINED_FRAMEWORK;
            break;
         }
      }
   }
   return ret_val;
}
