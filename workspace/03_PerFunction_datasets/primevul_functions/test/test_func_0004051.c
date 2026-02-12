void get_merge_candidate_list_without_step_9(base_context* ctx,
                                             const slice_segment_header* shdr,
                                             const MotionVectorAccess& mvaccess,
                                             de265_image* img,
                                             int xC,int yC, int xP,int yP,
                                             int nCS, int nPbW,int nPbH, int partIdx,
                                             int max_merge_idx,
                                             PBMotion* mergeCandList)
{


  int nOrigPbW = nPbW;
  int nOrigPbH = nPbH;

  int singleMCLFlag;


  singleMCLFlag = (img->get_pps().log2_parallel_merge_level > 2 && nCS==8);

  if (singleMCLFlag) {
    xP=xC;
    yP=yC;
    nPbW=nCS;
    nPbH=nCS;
    partIdx=0;
  }

  int maxCandidates = max_merge_idx+1;

  int numMergeCand=0;


  numMergeCand = derive_spatial_merging_candidates(mvaccess,
                                                   img, xC,yC, nCS, xP,yP, singleMCLFlag,
                                                   nPbW,nPbH,partIdx, mergeCandList,
                                                   maxCandidates);


  if (numMergeCand < maxCandidates) {
    int refIdxCol[2] = { 0,0 };

    MotionVector mvCol[2];
    uint8_t predFlagLCol[2];
    derive_temporal_luma_vector_prediction(ctx,img,shdr, xP,yP,nPbW,nPbH,
                                           refIdxCol[0],0, &mvCol[0],
                                           &predFlagLCol[0]);

    uint8_t availableFlagCol = predFlagLCol[0];
    predFlagLCol[1] = 0;

    if (shdr->slice_type == SLICE_TYPE_B) {
      derive_temporal_luma_vector_prediction(ctx,img,shdr,
                                             xP,yP,nPbW,nPbH, refIdxCol[1],1, &mvCol[1],
                                             &predFlagLCol[1]);
      availableFlagCol |= predFlagLCol[1];
    }


    if (availableFlagCol) {
      PBMotion* colVec = &mergeCandList[numMergeCand++];

      colVec->mv[0] = mvCol[0];
      colVec->mv[1] = mvCol[1];
      colVec->predFlag[0] = predFlagLCol[0];
      colVec->predFlag[1] = predFlagLCol[1];
      colVec->refIdx[0] = refIdxCol[0];
      colVec->refIdx[1] = refIdxCol[1];
    }
  }


  if (shdr->slice_type == SLICE_TYPE_B) {
    derive_combined_bipredictive_merging_candidates(ctx, shdr,
                                                    mergeCandList, &numMergeCand, maxCandidates);
  }


  derive_zero_motion_vector_candidates(shdr, mergeCandList, &numMergeCand, maxCandidates);


  logtrace(LogMotion,"mergeCandList:\n");
  for (int i=0;i<shdr->MaxNumMergeCand;i++)
    {

      logmvcand(mergeCandList[i]);
    }
}
