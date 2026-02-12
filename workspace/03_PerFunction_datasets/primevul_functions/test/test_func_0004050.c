void derive_collocated_motion_vectors(base_context* ctx,
                                      de265_image* img,
                                      const slice_segment_header* shdr,
                                      int xP,int yP,
                                      int colPic,
                                      int xColPb,int yColPb,
                                      int refIdxLX,
                                      int X,
                                      MotionVector* out_mvLXCol,
                                      uint8_t* out_availableFlagLXCol)
{
  logtrace(LogMotion,"derive_collocated_motion_vectors %d;%d\n",xP,yP);


  assert(ctx->has_image(colPic));
  const de265_image* colImg = ctx->get_image(colPic);


  if (xColPb >= colImg->get_width() ||
      yColPb >= colImg->get_height()) {
    ctx->add_warning(DE265_WARNING_COLLOCATED_MOTION_VECTOR_OUTSIDE_IMAGE_AREA, false);
    *out_availableFlagLXCol = 0;
    return;
  }

  enum PredMode predMode = colImg->get_pred_mode(xColPb,yColPb);


  if (predMode == MODE_INTRA) {
    out_mvLXCol->x = 0;
    out_mvLXCol->y = 0;
    *out_availableFlagLXCol = 0;
    return;
  }


  logtrace(LogMotion,"colPic:%d (POC=%d) X:%d refIdxLX:%d refpiclist:%d\n",
           colPic,
           colImg->PicOrderCntVal,
           X,refIdxLX,shdr->RefPicList[X][refIdxLX]);


  if (colImg->integrity == INTEGRITY_UNAVAILABLE_REFERENCE) {
    out_mvLXCol->x = 0;
    out_mvLXCol->y = 0;
    *out_availableFlagLXCol = 0;
    return;
  }


  const PBMotion& mvi = colImg->get_mv_info(xColPb,yColPb);
  int listCol;
  int refIdxCol;
  MotionVector mvCol;

  logtrace(LogMotion,"read MVI %d;%d:\n",xColPb,yColPb);
  logmvcand(mvi);


  if (mvi.predFlag[0]==0) {
    mvCol = mvi.mv[1];
    refIdxCol = mvi.refIdx[1];
    listCol = 1;
  }

  else if (mvi.predFlag[1]==0) {
    mvCol = mvi.mv[0];
    refIdxCol = mvi.refIdx[0];
    listCol = 0;
  }

  else {
    bool allRefFramesBeforeCurrentFrame = true;

    const int currentPOC = img->PicOrderCntVal;


    for (int rIdx=0; rIdx<shdr->num_ref_idx_l1_active && allRefFramesBeforeCurrentFrame; rIdx++)
      {
        const de265_image* refimg = ctx->get_image(shdr->RefPicList[1][rIdx]);
        int refPOC = refimg->PicOrderCntVal;

        if (refPOC > currentPOC) {
          allRefFramesBeforeCurrentFrame = false;
        }
      }


    for (int rIdx=0; rIdx<shdr->num_ref_idx_l0_active && allRefFramesBeforeCurrentFrame; rIdx++)
      {
        const de265_image* refimg = ctx->get_image(shdr->RefPicList[0][rIdx]);
        int refPOC = refimg->PicOrderCntVal;

        if (refPOC > currentPOC) {
          allRefFramesBeforeCurrentFrame = false;
        }
      }


    if (allRefFramesBeforeCurrentFrame) {
      mvCol = mvi.mv[X];
      refIdxCol = mvi.refIdx[X];
      listCol = X;
    }
    else {
      int N = shdr->collocated_from_l0_flag;
      mvCol = mvi.mv[N];
      refIdxCol = mvi.refIdx[N];
      listCol = N;
    }
  }


  const slice_segment_header* colShdr = colImg->slices[ colImg->get_SliceHeaderIndex(xColPb,yColPb) ];

  if (shdr->LongTermRefPic[X][refIdxLX] !=
      colShdr->LongTermRefPic[listCol][refIdxCol]) {
    *out_availableFlagLXCol = 0;
    out_mvLXCol->x = 0;
    out_mvLXCol->y = 0;
  }
  else {
    *out_availableFlagLXCol = 1;

    const bool isLongTerm = shdr->LongTermRefPic[X][refIdxLX];

    int colDist  = colImg->PicOrderCntVal - colShdr->RefPicList_POC[listCol][refIdxCol];
    int currDist = img->PicOrderCntVal - shdr->RefPicList_POC[X][refIdxLX];

    logtrace(LogMotion,"COLPOCDIFF %d %d [%d %d / %d %d]\n",colDist, currDist,
             colImg->PicOrderCntVal, colShdr->RefPicList_POC[listCol][refIdxCol],
             img->PicOrderCntVal, shdr->RefPicList_POC[X][refIdxLX]
             );

    if (isLongTerm || colDist == currDist) {
      *out_mvLXCol = mvCol;
    }
    else {
      if (!scale_mv(out_mvLXCol, mvCol, colDist, currDist)) {
        ctx->add_warning(DE265_WARNING_INCORRECT_MOTION_VECTOR_SCALING, false);
        img->integrity = INTEGRITY_DECODING_ERRORS;
      }

      logtrace(LogMotion,"scale: %d;%d to %d;%d\n",
               mvCol.x,mvCol.y, out_mvLXCol->x,out_mvLXCol->y);
    }
  }
}
