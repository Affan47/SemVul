rv34_mc_2mv(RV34DecContext *r, const int block_type)
{
    rv34_mc(r, block_type, 0, 0, 0, 2, 2, 0, r->rv30,
            r->rv30 ? r->s.dsp.put_rv30_tpel_pixels_tab
                    : r->s.dsp.put_rv40_qpel_pixels_tab,
            r->rv30 ? r->s.dsp.put_h264_chroma_pixels_tab
                    : r->s.dsp.put_rv40_chroma_pixels_tab);
    rv34_mc(r, block_type, 0, 0, 0, 2, 2, 1, r->rv30,
            r->rv30 ? r->s.dsp.avg_rv30_tpel_pixels_tab
                    : r->s.dsp.avg_rv40_qpel_pixels_tab,
            r->rv30 ? r->s.dsp.avg_h264_chroma_pixels_tab
                    : r->s.dsp.avg_rv40_chroma_pixels_tab);
}
