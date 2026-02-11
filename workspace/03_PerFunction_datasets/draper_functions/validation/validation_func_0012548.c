IDirectFBDisplayLayer_TestConfiguration( IDirectFBDisplayLayer       *thiz,
                                         const DFBDisplayLayerConfig *config,
                                         DFBDisplayLayerConfigFlags  *failed )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBDisplayLayer)

     if (!config)
          return DFB_INVARG;

     if (((config->flags & DLCONF_WIDTH) && (config->width < 0)) ||
         ((config->flags & DLCONF_HEIGHT) && (config->height < 0)))
          return DFB_INVARG;

     return dfb_layer_context_test_configuration( data->context, config, failed );
}
