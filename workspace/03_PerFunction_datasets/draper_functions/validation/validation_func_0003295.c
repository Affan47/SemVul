GRsetcompress(int32 riid,comp_coder_t comp_type,comp_info *cinfo)
{
    CONSTR(FUNC, "GRsetcompress");
    ri_info_t *ri_ptr;
    comp_info cinfo_x;
    uint32 comp_config;
    intn  ret_value = SUCCEED;


    HEclear();

    HDmemcpy(&cinfo_x,cinfo,sizeof(comp_info));

    if (HAatom_group(riid)!=RIIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    if ((comp_type < COMP_CODE_NONE || comp_type >= COMP_CODE_INVALID)
  && comp_type!=COMP_CODE_JPEG)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    if (NULL == (ri_ptr = (ri_info_t *) HAatom_object(riid)))
        HGOTO_ERROR(DFE_RINOTFOUND, FAIL);


    if (ri_ptr->use_buf_drvr)
        HGOTO_ERROR(DFE_CANTMOD, FAIL);


    HCget_config_info(comp_type, &comp_config);
    if ((comp_config & COMP_DECODER_ENABLED|COMP_ENCODER_ENABLED) == 0) {

      HGOTO_ERROR(DFE_BADCODER, FAIL);
    }
    if ((comp_config & COMP_ENCODER_ENABLED) != COMP_ENCODER_ENABLED) {


      HGOTO_ERROR(DFE_NOENCODER, FAIL);
    }

    if (comp_type==COMP_CODE_SZIP)
#ifndef H4_HAVE_LIBSZ
        HGOTO_ERROR(DFE_NOSZLIB, FAIL);
#else
    {

  if (GRsetup_szip_parms( ri_ptr, &cinfo_x, NULL) == FAIL) {
      HGOTO_ERROR(DFE_INTERNAL, FAIL);
  }
    }
#endif


    if(comp_type==COMP_CODE_JPEG)
      {
        if(ri_ptr->img_dim.ncomps==1)
            ri_ptr->img_dim.comp_tag=DFTAG_GREYJPEG5;
        else if(ri_ptr->img_dim.ncomps==3)
            ri_ptr->img_dim.comp_tag=DFTAG_JPEG5;
        else
            HGOTO_ERROR(DFE_CANTMOD, FAIL);
        ri_ptr->use_cr_drvr=TRUE;
      }
    else
      {
        ri_ptr->comp_img=TRUE;
        ri_ptr->comp_type=comp_type;
      }


    HDmemcpy(&(ri_ptr->cinfo),&cinfo_x,sizeof(comp_info));


    ri_ptr->use_buf_drvr=1;


    if(GRIgetaid(ri_ptr, DFACC_WRITE)==FAIL)
        HGOTO_ERROR(DFE_INTERNAL,FAIL);

done:
  if(ret_value == 0)
    {

    }


  return ret_value;
}
