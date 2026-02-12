static void paste_option_changed(void)
{
  static int old_p_paste = FALSE;
  static int save_sm = 0;
  static int save_sta = 0;
  static int save_ru = 0;
  static int save_ri = 0;
  static int save_hkmap = 0;

  if (p_paste) {


    if (!old_p_paste) {

      FOR_ALL_BUFFERS(buf) {
        buf->b_p_tw_nopaste = buf->b_p_tw;
        buf->b_p_wm_nopaste = buf->b_p_wm;
        buf->b_p_sts_nopaste = buf->b_p_sts;
        buf->b_p_ai_nopaste = buf->b_p_ai;
        buf->b_p_et_nopaste = buf->b_p_et;
      }


      save_sm = p_sm;
      save_sta = p_sta;
      save_ru = p_ru;
      save_ri = p_ri;
      save_hkmap = p_hkmap;

      p_ai_nopaste = p_ai;
      p_et_nopaste = p_et;
      p_sts_nopaste = p_sts;
      p_tw_nopaste = p_tw;
      p_wm_nopaste = p_wm;
    }


    FOR_ALL_BUFFERS(buf) {
      buf->b_p_tw = 0;
      buf->b_p_wm = 0;
      buf->b_p_sts = 0;
      buf->b_p_ai = 0;
      buf->b_p_et = 0;
    }


    p_sm = 0;
    p_sta = 0;
    if (p_ru) {
      status_redraw_all();
    }
    p_ru = 0;
    p_ri = 0;
    p_hkmap = 0;

    p_tw = 0;
    p_wm = 0;
    p_sts = 0;
    p_ai = 0;
  }


  else if (old_p_paste) {

    FOR_ALL_BUFFERS(buf) {
      buf->b_p_tw = buf->b_p_tw_nopaste;
      buf->b_p_wm = buf->b_p_wm_nopaste;
      buf->b_p_sts = buf->b_p_sts_nopaste;
      buf->b_p_ai = buf->b_p_ai_nopaste;
      buf->b_p_et = buf->b_p_et_nopaste;
    }


    p_sm = save_sm;
    p_sta = save_sta;
    if (p_ru != save_ru) {
      status_redraw_all();
    }
    p_ru = save_ru;
    p_ri = save_ri;
    p_hkmap = save_hkmap;

    p_ai = p_ai_nopaste;
    p_et = p_et_nopaste;
    p_sts = p_sts_nopaste;
    p_tw = p_tw_nopaste;
    p_wm = p_wm_nopaste;
  }

  old_p_paste = p_paste;
}
