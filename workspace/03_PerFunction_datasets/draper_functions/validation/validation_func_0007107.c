gss_wrap (OM_uint32 * minor_status,
	  const gss_ctx_id_t context_handle,
	  int conf_req_flag,
	  gss_qop_t qop_req,
	  const gss_buffer_t input_message_buffer,
	  int *conf_state, gss_buffer_t output_message_buffer)
{
  _gss_mech_api_t mech;

  if (!context_handle)
    {
      if (minor_status)
	*minor_status = 0;
      return GSS_S_NO_CONTEXT;
    }

  mech = _gss_find_mech (context_handle->mech);
  if (mech == NULL)
    {
      if (minor_status)
	*minor_status = 0;
      return GSS_S_BAD_MECH;
    }

  return mech->wrap (minor_status, context_handle, conf_req_flag, qop_req,
		     input_message_buffer, conf_state, output_message_buffer);
}
