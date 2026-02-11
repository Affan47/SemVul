wv_dcma(p_dc)

p_dc_t p_dc;
{
 p_bp_t p_bp;
 p_ma_t p_ma  = p_dc->dc_p_ma;
 ulong  level = p_dc->dc_mlev;
 p_md_t p_md  = &p_ma->ma_defn[level];


 ls_loo(p_md->md_body,p_dc->dc_part,PPV &p_bp);


 wf_wl(&f_t,"<FONT COLOR=#CC0033>");

 wf_wr(&f_t,"<P><A NAME=\"");
 wf_dec(&f_t,(ulong) p_bp->bp_seq);
 wf_wr(&f_t,"\"></A>");


 if (p_md->md_isfil)
    wf_wr(&f_t,"<B>");
 wf_dec(&f_t,(ulong) p_bp->bp_seq);
 wf_wr(&f_t,". ");
 if (p_md->md_isfil)
    wf_wr(&f_t,"File:</B> ");


 {
  bool called = wv_fcall(p_ma);
  wv_ugstr(p_ma->ma_name,EOL_BR_NO);
  if (called) wf_wr(&f_t,"</A>");
 }


 if (p_md->md_npar>0)
   {
    wf_wr(&f_t,"(<B>");
    wf_dec(&f_t,(ulong) p_md->md_npar);
    wf_wr(&f_t,"</B>)");
   }


 if ((p_md->md_iszer) || (p_md->md_isman) || (level > 0))
   {
    ulong i;
    wf_wr(&f_t,"[<B>");
    if (p_md->md_iszer) wf_wr(&f_t,"Z");
    if (p_md->md_isman) wf_wr(&f_t,"M");
    for (i=0; i<level; i++) wf_wr(&f_t,"L");
    wf_wr(&f_t,"</B>]");
   }


 if (p_md->md_isadd)
    wf_wr(&f_t,"+=");
 else
    wf_wr(&f_t,"=");


 wf_wr(&f_t,"{");


 wf_wr(&f_t,"<FONT COLOR=#000033>");
 wv_ex(p_bp->bp_ex);
 wf_wr(&f_t,"</FONT>");


 wf_wl(&f_t,"}<BR>");


 wf_wl(&f_t,"</FONT>");


 wv_defin(p_ma,level);
 wv_usage(p_ma,level);
}
