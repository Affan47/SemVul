void fill_luma_motion_vector_predictors(base_context* ctx,
                                        const slice_segment_header* shdr,
                                        de265_image* img,
                                        int xC,int yC,int nCS,int xP,int yP,
                                        int nPbW,int nPbH, int l,
                                        int refIdx, int partIdx,
                                        MotionVector out_mvpList[2])
{


  uint8_t availableFlagLXN[2];
  MotionVector mvLXN[2];

  derive_spatial_luma_vector_prediction(ctx, img, shdr, xC,yC, nCS, xP,yP,
                                        nPbW,nPbH, l, refIdx, partIdx,
                                        availableFlagLXN, mvLXN);


  uint8_t availableFlagLXCol;
  MotionVector mvLXCol;


  if (availableFlagLXN[0] &&
      availableFlagLXN[1] &&
      (mvLXN[0].x != mvLXN[1].x || mvLXN[0].y != mvLXN[1].y)) {
    availableFlagLXCol = 0;
  }
  else {
    derive_temporal_luma_vector_prediction(ctx, img, shdr,
                                           xP,yP, nPbW,nPbH, refIdx,l,
                                           &mvLXCol, &availableFlagLXCol);
  }


  int numMVPCandLX=0;


  if (availableFlagLXN[0])
    {
      out_mvpList[numMVPCandLX++] = mvLXN[0];
    }


  if (availableFlagLXN[1] &&
      (!availableFlagLXN[0] ||
       (mvLXN[0].x != mvLXN[1].x || mvLXN[0].y != mvLXN[1].y)))
    {
      out_mvpList[numMVPCandLX++] = mvLXN[1];
    }


  if (availableFlagLXCol)
    {
      out_mvpList[numMVPCandLX++] = mvLXCol;
    }


  while (numMVPCandLX<2) {
    out_mvpList[numMVPCandLX].x = 0;
    out_mvpList[numMVPCandLX].y = 0;
    numMVPCandLX++;
  }


  assert(numMVPCandLX==2);
}
