gst_pngdec_stop (GstVideoDecoder * decoder)
{
  GstPngDec *pngdec = (GstPngDec *) decoder;

  gst_pngdec_libpng_clear (pngdec);

  if (pngdec->input_state) {
    gst_video_codec_state_unref (pngdec->input_state);
    pngdec->input_state = NULL;
  }
  if (pngdec->output_state) {
    gst_video_codec_state_unref (pngdec->output_state);
    pngdec->output_state = NULL;
  }

  return TRUE;
}
