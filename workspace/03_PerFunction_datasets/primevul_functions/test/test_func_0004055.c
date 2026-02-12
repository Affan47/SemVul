void derive_spatial_luma_vector_prediction(base_context* ctx,
                                           de265_image* img,
                                           const slice_segment_header* shdr,
                                           int xC,int yC,int nCS,int xP,int yP,
                                           int nPbW,int nPbH, int X,
                                           int refIdxLX, int partIdx,
                                           uint8_t out_availableFlagLXN[2],
                                           MotionVector out_mvLXN[2])
{
  int isScaledFlagLX = 0;

  const int A=0;
  const int B=1;

  out_availableFlagLXN[A] = 0;
  out_availableFlagLXN[B] = 0;


  int xA[2], yA[2];
  xA[0] = xP-1;
  yA[0] = yP + nPbH;
  xA[1] = xA[0];
  yA[1] = yA[0]-1;


  out_availableFlagLXN[A] = 0;
  out_mvLXN[A].x = 0;
  out_mvLXN[A].y = 0;


  bool availableA[2];
  availableA[0] = img->available_pred_blk(xC,yC, nCS, xP,yP, nPbW,nPbH,partIdx, xA[0],yA[0]);
  availableA[1] = img->available_pred_blk(xC,yC, nCS, xP,yP, nPbW,nPbH,partIdx, xA[1],yA[1]);


  if (availableA[0] || availableA[1]) {
    isScaledFlagLX = 1;
  }


  int refIdxA=-1;


  const de265_image* tmpimg = ctx->get_image(shdr->RefPicList[X][ refIdxLX ]);
  if (tmpimg==NULL) { return; }
  const int referenced_POC = tmpimg->PicOrderCntVal;

  for (int k=0;k<=1;k++) {
    if (availableA[k] &&
        out_availableFlagLXN[A]==0 &&
        img->get_pred_mode(xA[k],yA[k]) != MODE_INTRA) {

      int Y=1-X;

      const PBMotion& vi = img->get_mv_info(xA[k],yA[k]);
      logtrace(LogMotion,"MVP A%d=\n",k);
      logmvcand(vi);

      const de265_image* imgX = NULL;
      if (vi.predFlag[X]) imgX = ctx->get_image(shdr->RefPicList[X][ vi.refIdx[X] ]);
      const de265_image* imgY = NULL;
      if (vi.predFlag[Y]) imgY = ctx->get_image(shdr->RefPicList[Y][ vi.refIdx[Y] ]);


      if (vi.predFlag[X] && imgX && imgX->PicOrderCntVal == referenced_POC) {

        logtrace(LogMotion,"take A%d/L%d as A candidate with same POC\n",k,X);

        out_availableFlagLXN[A]=1;
        out_mvLXN[A] = vi.mv[X];
        refIdxA = vi.refIdx[X];
      }

      else if (vi.predFlag[Y] && imgY && imgY->PicOrderCntVal == referenced_POC) {

        logtrace(LogMotion,"take A%d/L%d as A candidate with same POC\n",k,Y);

        out_availableFlagLXN[A]=1;
        out_mvLXN[A] = vi.mv[Y];
        refIdxA = vi.refIdx[Y];
      }
    }
  }


  for (int k=0 ; k<=1 && out_availableFlagLXN[A]==0 ; k++) {
    int refPicList=-1;

    if (availableA[k] &&

        img->get_pred_mode(xA[k],yA[k]) != MODE_INTRA) {

      int Y=1-X;

      const PBMotion& vi = img->get_mv_info(xA[k],yA[k]);
      if (vi.predFlag[X]==1 &&
          shdr->LongTermRefPic[X][refIdxLX] == shdr->LongTermRefPic[X][ vi.refIdx[X] ]) {

        logtrace(LogMotion,"take A%D/L%d as A candidate with different POCs\n",k,X);

        out_availableFlagLXN[A]=1;
        out_mvLXN[A] = vi.mv[X];
        refIdxA = vi.refIdx[X];
        refPicList = X;
      }
      else if (vi.predFlag[Y]==1 &&
               shdr->LongTermRefPic[X][refIdxLX] == shdr->LongTermRefPic[Y][ vi.refIdx[Y] ]) {

        logtrace(LogMotion,"take A%d/L%d as A candidate with different POCs\n",k,Y);

        out_availableFlagLXN[A]=1;
        out_mvLXN[A] = vi.mv[Y];
        refIdxA = vi.refIdx[Y];
        refPicList = Y;
      }
    }

    if (out_availableFlagLXN[A]==1) {
      if (refIdxA<0) {
        out_availableFlagLXN[0] = out_availableFlagLXN[1] = false;
        return;
      }

      assert(refIdxA>=0);
      assert(refPicList>=0);

      const de265_image* refPicA = ctx->get_image(shdr->RefPicList[refPicList][refIdxA ]);
      const de265_image* refPicX = ctx->get_image(shdr->RefPicList[X         ][refIdxLX]);


      int isLongTermA = shdr->LongTermRefPic[refPicList][refIdxA ];
      int isLongTermX = shdr->LongTermRefPic[X         ][refIdxLX];

      logtrace(LogMotion,"scale MVP A: A-POC:%d X-POC:%d\n",
               refPicA->PicOrderCntVal,refPicX->PicOrderCntVal);

      if (!isLongTermA && !isLongTermX)


        {
          int distA = img->PicOrderCntVal - refPicA->PicOrderCntVal;
          int distX = img->PicOrderCntVal - referenced_POC;

          if (!scale_mv(&out_mvLXN[A], out_mvLXN[A], distA, distX)) {
            ctx->add_warning(DE265_WARNING_INCORRECT_MOTION_VECTOR_SCALING, false);
            img->integrity = INTEGRITY_DECODING_ERRORS;
          }
        }
    }
  }


  int xB[3], yB[3];
  xB[0] = xP+nPbW;
  yB[0] = yP-1;
  xB[1] = xB[0]-1;
  yB[1] = yP-1;
  xB[2] = xP-1;
  yB[2] = yP-1;


  out_availableFlagLXN[B] = 0;
  out_mvLXN[B].x = 0;
  out_mvLXN[B].y = 0;


  int refIdxB=-1;

  bool availableB[3];
  for (int k=0;k<3;k++) {
    availableB[k] = img->available_pred_blk(xC,yC, nCS, xP,yP, nPbW,nPbH,partIdx, xB[k],yB[k]);

    if (availableB[k] && out_availableFlagLXN[B]==0) {

      int Y=1-X;

      const PBMotion& vi = img->get_mv_info(xB[k],yB[k]);
      logtrace(LogMotion,"MVP B%d=\n",k);
      logmvcand(vi);


      const de265_image* imgX = NULL;
      if (vi.predFlag[X]) imgX = ctx->get_image(shdr->RefPicList[X][ vi.refIdx[X] ]);
      const de265_image* imgY = NULL;
      if (vi.predFlag[Y]) imgY = ctx->get_image(shdr->RefPicList[Y][ vi.refIdx[Y] ]);

      if (vi.predFlag[X] && imgX && imgX->PicOrderCntVal == referenced_POC) {
        logtrace(LogMotion,"a) take B%d/L%d as B candidate with same POC\n",k,X);

        out_availableFlagLXN[B]=1;
        out_mvLXN[B] = vi.mv[X];
        refIdxB = vi.refIdx[X];
      }
      else if (vi.predFlag[Y] && imgY && imgY->PicOrderCntVal == referenced_POC) {
        logtrace(LogMotion,"b) take B%d/L%d as B candidate with same POC\n",k,Y);

        out_availableFlagLXN[B]=1;
        out_mvLXN[B] = vi.mv[Y];
        refIdxB = vi.refIdx[Y];
      }
    }
  }


  if (isScaledFlagLX==0 &&
      out_availableFlagLXN[B])
    {


      logtrace(LogMotion,"copy the same-POC B candidate as additional A candidate\n");

      out_availableFlagLXN[A]=1;
      out_mvLXN[A] = out_mvLXN[B];
      refIdxA = refIdxB;
    }


  if (isScaledFlagLX==0) {
    out_availableFlagLXN[B]=0;

    for (int k=0 ; k<=2 && out_availableFlagLXN[B]==0 ; k++) {
      int refPicList=-1;

      if (availableB[k]) {
        int Y=1-X;

        const PBMotion& vi = img->get_mv_info(xB[k],yB[k]);

        if (vi.predFlag[X]==1 &&
            shdr->LongTermRefPic[X][refIdxLX] == shdr->LongTermRefPic[X][ vi.refIdx[X] ]) {
          out_availableFlagLXN[B]=1;
          out_mvLXN[B] = vi.mv[X];
          refIdxB = vi.refIdx[X];
          refPicList = X;
        }
        else if (vi.predFlag[Y]==1 &&
                 shdr->LongTermRefPic[X][refIdxLX] == shdr->LongTermRefPic[Y][ vi.refIdx[Y] ]) {
          out_availableFlagLXN[B]=1;
          out_mvLXN[B] = vi.mv[Y];
          refIdxB = vi.refIdx[Y];
          refPicList = Y;
        }
      }

      if (out_availableFlagLXN[B]==1) {
        if (refIdxB<0) {
          out_availableFlagLXN[0] = out_availableFlagLXN[1] = false;
          return;
        }

        assert(refPicList>=0);
        assert(refIdxB>=0);

        const de265_image* refPicB=ctx->get_image(shdr->RefPicList[refPicList][refIdxB ]);
        const de265_image* refPicX=ctx->get_image(shdr->RefPicList[X         ][refIdxLX]);

        int isLongTermB = shdr->LongTermRefPic[refPicList][refIdxB ];
        int isLongTermX = shdr->LongTermRefPic[X         ][refIdxLX];

        if (refPicB==NULL || refPicX==NULL) {
          img->decctx->add_warning(DE265_WARNING_NONEXISTING_REFERENCE_PICTURE_ACCESSED,false);
          img->integrity = INTEGRITY_DECODING_ERRORS;
        }
        else if (refPicB->PicOrderCntVal != refPicX->PicOrderCntVal &&
                 !isLongTermB && !isLongTermX) {
          int distB = img->PicOrderCntVal - refPicB->PicOrderCntVal;
          int distX = img->PicOrderCntVal - referenced_POC;

          logtrace(LogMotion,"scale MVP B: B-POC:%d X-POC:%d\n",refPicB->PicOrderCntVal,refPicX->PicOrderCntVal);

          if (!scale_mv(&out_mvLXN[B], out_mvLXN[B], distB, distX)) {
            ctx->add_warning(DE265_WARNING_INCORRECT_MOTION_VECTOR_SCALING, false);
            img->integrity = INTEGRITY_DECODING_ERRORS;
          }
        }
      }
    }
  }
}
