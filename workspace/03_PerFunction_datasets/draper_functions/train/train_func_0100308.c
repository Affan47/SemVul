IDirectFB_Construct( IDirectFB *thiz, CoreDFB *core )
{
     DFBResult ret;

     DIRECT_ALLOCATE_INTERFACE_DATA(thiz, IDirectFB)

     D_DEBUG_AT( IDFB, "%s( %p, %p )\n", __FUNCTION__, thiz, core );

     data->ref   = 1;
     data->core  = core;
     data->level = DFSCL_NORMAL;

     if (dfb_layer_num() < 1) {
          D_ERROR( "%s: No layers available! Missing driver?\n", __FUNCTION__ );
          return DFB_UNSUPPORTED;
     }

     data->layer = dfb_layer_at_translated( DLID_PRIMARY );

     ret = dfb_layer_get_primary_context( data->layer, true, &data->context );
     if (ret) {
          D_ERROR( "%s: Could not get default context of primary layer!\n", __FUNCTION__ );
          DIRECT_DEALLOCATE_INTERFACE(thiz);
          return ret;
     }

     data->stack = dfb_layer_context_windowstack( data->context );

     thiz->AddRef = IDirectFB_AddRef;
     thiz->Release = IDirectFB_Release;
     thiz->SetCooperativeLevel = IDirectFB_SetCooperativeLevel;
     thiz->GetDeviceDescription = IDirectFB_GetDeviceDescription;
     thiz->EnumVideoModes = IDirectFB_EnumVideoModes;
     thiz->SetVideoMode = IDirectFB_SetVideoMode;
     thiz->CreateSurface = IDirectFB_CreateSurface;
     thiz->CreatePalette = IDirectFB_CreatePalette;
     thiz->EnumScreens = IDirectFB_EnumScreens;
     thiz->GetScreen = IDirectFB_GetScreen;
     thiz->EnumDisplayLayers = IDirectFB_EnumDisplayLayers;
     thiz->GetDisplayLayer = IDirectFB_GetDisplayLayer;
     thiz->EnumInputDevices = IDirectFB_EnumInputDevices;
     thiz->GetInputDevice = IDirectFB_GetInputDevice;
     thiz->CreateEventBuffer = IDirectFB_CreateEventBuffer;
     thiz->CreateInputEventBuffer = IDirectFB_CreateInputEventBuffer;
     thiz->CreateImageProvider = IDirectFB_CreateImageProvider;
     thiz->CreateVideoProvider = IDirectFB_CreateVideoProvider;
     thiz->CreateFont = IDirectFB_CreateFont;
     thiz->CreateDataBuffer = IDirectFB_CreateDataBuffer;
     thiz->SetClipboardData = IDirectFB_SetClipboardData;
     thiz->GetClipboardData = IDirectFB_GetClipboardData;
     thiz->GetClipboardTimeStamp = IDirectFB_GetClipboardTimeStamp;
     thiz->Suspend = IDirectFB_Suspend;
     thiz->Resume = IDirectFB_Resume;
     thiz->WaitIdle = IDirectFB_WaitIdle;
     thiz->WaitForSync = IDirectFB_WaitForSync;
     thiz->GetInterface = IDirectFB_GetInterface;

     if (dfb_core_is_master( core )) {
          ret = InitLayers( thiz, data );
          if (ret) {
               dfb_layer_context_unref( data->context );
               DIRECT_DEALLOCATE_INTERFACE(thiz);
               return ret;
          }
     }

     return DFB_OK;
}
