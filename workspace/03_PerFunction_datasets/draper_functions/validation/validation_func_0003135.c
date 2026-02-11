jpeg_consume_input (j_decompress_ptr cinfo)
{
  int retcode = JPEG_SUSPENDED;


  switch (cinfo->global_state) {
  case DSTATE_START:

    (*cinfo->inputctl->reset_input_controller) (cinfo);

    (*cinfo->src->init_source) (cinfo);
    cinfo->global_state = DSTATE_INHEADER;

  case DSTATE_INHEADER:
    retcode = (*cinfo->inputctl->consume_input) (cinfo);
    if (retcode == JPEG_REACHED_SOS) {

      default_decompress_parms(cinfo);

      cinfo->global_state = DSTATE_READY;
    }
    break;
  case DSTATE_READY:

    retcode = JPEG_REACHED_SOS;
    break;
  case DSTATE_PRELOAD:
  case DSTATE_PRESCAN:
  case DSTATE_SCANNING:
  case DSTATE_RAW_OK:
  case DSTATE_BUFIMAGE:
  case DSTATE_BUFPOST:
  case DSTATE_STOPPING:
    retcode = (*cinfo->inputctl->consume_input) (cinfo);
    break;
  default:
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  }
  return retcode;
}
