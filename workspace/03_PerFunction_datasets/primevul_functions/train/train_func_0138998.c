static OPJ_OFF_T jpxSkip_callback(OPJ_OFF_T skip, void * p_user_data)
{
  JPXData *jpxData = (JPXData *)p_user_data;

  jpxData->pos += (skip > jpxData->size - jpxData->pos) ? jpxData->size - jpxData->pos : skip;

  return skip;
}
