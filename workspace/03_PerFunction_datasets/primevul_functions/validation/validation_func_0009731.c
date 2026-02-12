check_dnp3_header(tvbuff_t *tvb, gboolean dnp3_heuristics)
{

  gboolean goodCRC = FALSE;


  gint length = tvb_captured_length(tvb);


  if (length >= DNP_HDR_LEN) {
    guint16 calc_crc = calculateCRCtvb(tvb, 0, DNP_HDR_LEN - 2);
    goodCRC = (calc_crc == tvb_get_letohs(tvb, 8));
  }


  if (dnp3_heuristics) {
    if ( !goodCRC || (tvb_get_ntohs(tvb, 0) != 0x0564)) {
      return FALSE;
    }
  }
  else {


    if (tvb_get_guint8(tvb, 0) != 0x05) {
      return FALSE;
    }
    if ((length > 1) && (tvb_get_guint8(tvb, 1) != 0x64)) {
      return FALSE;
    }
    if ((length >= DNP_HDR_LEN) && !goodCRC) {
      return FALSE;
    }
  }
  return TRUE;
}
