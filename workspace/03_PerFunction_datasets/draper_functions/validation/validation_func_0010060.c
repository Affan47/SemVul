IDirectFBWindow_SetApplicationID( IDirectFBWindow *thiz,
                                  unsigned long    application_id )

{
     CoreWindowConfig config;

     DIRECT_INTERFACE_GET_DATA(IDirectFBWindow)

     D_DEBUG_AT( IDirectFB_Window, "%s()\n", __FUNCTION__ );

     if (data->destroyed)
          return DFB_DESTROYED;

     config.application_id = application_id;

     return dfb_window_set_config( data->window, &config, CWCF_APPLICATION_ID );
}
