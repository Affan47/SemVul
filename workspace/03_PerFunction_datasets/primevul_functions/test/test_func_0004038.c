void derive_temporal_luma_vector_prediction(base_context* ctx,
                                            de265_image* img,
                                            const slice_segment_header* shdr,
                                            int xP,int yP,
                                            int nPbW,int nPbH,
                                            int refIdxL,
                                            int X,
                                            MotionVector* out_mvLXCol,
                                            uint8_t*      out_availableFlagLXCol)
{


  if (shdr->slice_temporal_mvp_enabled_flag == 0) {
    out_mvLXCol->x = 0;
    out_mvLXCol->y = 0;
    *out_availableFlagLXCol = 0;
    return;
  }


  int Log2CtbSizeY = img->get_sps().Log2CtbSizeY;

  int colPic;

  if (shdr->slice_type == SLICE_TYPE_B &&
      shdr->collocated_from_l0_flag == 0)
    {
      logtrace(LogMotion,"collocated L1 ref_idx=%d\n",shdr->collocated_ref_idx);

      colPic = shdr->RefPicList[1][ shdr->collocated_ref_idx ];
    }
  else
    {
      logtrace(LogMotion,"collocated L0 ref_idx=%d\n",shdr->collocated_ref_idx);

      colPic = shdr->RefPicList[0][ shdr->collocated_ref_idx ];
    }


  if (!ctx->has_image(colPic)) {
    out_mvLXCol->x = 0;
    out_mvLXCol->y = 0;
    *out_availableFlagLXCol = 0;

    ctx->add_warning(DE265_WARNING_NONEXISTING_REFERENCE_PICTURE_ACCESSED, false);
    return;
  }


  int xColPb,yColPb;
  int yColBr = yP + nPbH;
  int xColBr = xP + nPbW;


  if ((yP>>Log2CtbSizeY) == (yColBr>>Log2CtbSizeY) &&
      xColBr < img->get_sps().pic_width_in_luma_samples &&
      yColBr < img->get_sps().pic_height_in_luma_samples)
    {
      xColPb = xColBr & ~0x0F;
      yColPb = yColBr & ~0x0F;

      derive_collocated_motion_vectors(ctx,img,shdr, xP,yP, colPic, xColPb,yColPb, refIdxL, X,
                                       out_mvLXCol, out_availableFlagLXCol);
    }
  else
    {
      out_mvLXCol->x = 0;
      out_mvLXCol->y = 0;
      *out_availableFlagLXCol = 0;
    }


  if (*out_availableFlagLXCol==0) {

    int xColCtr = xP+(nPbW>>1);
    int yColCtr = yP+(nPbH>>1);

    xColPb = xColCtr & ~0x0F;
    yColPb = yColCtr & ~0x0F;

    derive_collocated_motion_vectors(ctx,img,shdr, xP,yP, colPic, xColPb,yColPb, refIdxL, X,
                                     out_mvLXCol, out_availableFlagLXCol);
  }
}
