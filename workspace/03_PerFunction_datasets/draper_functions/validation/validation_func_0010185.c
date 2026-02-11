IDirectFBFont_SetEncoding( IDirectFBFont     *thiz,
                           DFBTextEncodingID  encoding )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBFont)

     D_DEBUG_AT( Font, "%s( %p, %d )\n", __FUNCTION__, thiz, encoding );

     if (encoding > data->font->last_encoding)
          return DFB_IDNOTFOUND;

     data->encoding = encoding;

     return DFB_OK;
}
