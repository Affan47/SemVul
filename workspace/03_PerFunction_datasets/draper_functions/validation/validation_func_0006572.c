IDirectFBInputDevice_CreateEventBuffer( IDirectFBInputDevice  *thiz,
                                        IDirectFBEventBuffer **buffer )
{
     IDirectFBEventBuffer *b;

     DIRECT_INTERFACE_GET_DATA(IDirectFBInputDevice)

     DIRECT_ALLOCATE_INTERFACE( b, IDirectFBEventBuffer );

     IDirectFBEventBuffer_Construct( b, NULL, NULL );

     IDirectFBEventBuffer_AttachInputDevice( b, data->device );

     *buffer = b;

     return DFB_OK;
}
