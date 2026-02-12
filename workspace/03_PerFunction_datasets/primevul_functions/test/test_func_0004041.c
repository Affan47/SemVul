int derive_spatial_merging_candidates(
                                      const MotionVectorAccess& mvaccess,
                                      const de265_image* img,
                                      int xC, int yC, int nCS, int xP, int yP,
                                      uint8_t singleMCLFlag,
                                      int nPbW, int nPbH,
                                      int partIdx,
                                      PBMotion* out_cand,
                                      int maxCandidates)
{
  const pic_parameter_set* pps = &img->get_pps();
  const int log2_parallel_merge_level = pps->log2_parallel_merge_level;

  enum PartMode PartMode = mvaccess.get_PartMode(xC,yC);


  int xA1 = xP-1;
  int yA1 = yP+nPbH-1;

  bool availableA1;
  int idxA1;

  int computed_candidates = 0;


  if ((xP>>log2_parallel_merge_level) == (xA1>>log2_parallel_merge_level) &&
      (yP>>log2_parallel_merge_level) == (yA1>>log2_parallel_merge_level)) {
    availableA1 = false;
    logtrace(LogMotion,"spatial merging candidate A1: below parallel merge level\n");
  }

  else if (
           partIdx==1 &&
           (PartMode==PART_Nx2N ||
            PartMode==PART_nLx2N ||
            PartMode==PART_nRx2N)) {
    availableA1 = false;
    logtrace(LogMotion,"spatial merging candidate A1: second part ignore\n");
  }

  else {
    availableA1 = img->available_pred_blk(xC,yC, nCS, xP,yP, nPbW,nPbH,partIdx, xA1,yA1);
    if (!availableA1) logtrace(LogMotion,"spatial merging candidate A1: unavailable\n");
  }

  if (availableA1) {
    idxA1 = computed_candidates++;
    out_cand[idxA1] = mvaccess.get_mv_info(xA1,yA1);

    logtrace(LogMotion,"spatial merging candidate A1:\n");
    logmvcand(out_cand[idxA1]);
  }

  if (computed_candidates>=maxCandidates) return computed_candidates;


  int xB1 = xP+nPbW-1;
  int yB1 = yP-1;

  bool availableB1;
  int idxB1;


  if ((xP>>log2_parallel_merge_level) == (xB1>>log2_parallel_merge_level) &&
      (yP>>log2_parallel_merge_level) == (yB1>>log2_parallel_merge_level)) {
    availableB1 = false;
    logtrace(LogMotion,"spatial merging candidate B1: below parallel merge level\n");
  }

  else if (
           partIdx==1 &&
           (PartMode==PART_2NxN ||
            PartMode==PART_2NxnU ||
            PartMode==PART_2NxnD)) {
    availableB1 = false;
    logtrace(LogMotion,"spatial merging candidate B1: second part ignore\n");
  }

  else {
    availableB1 = img->available_pred_blk(xC,yC, nCS, xP,yP, nPbW,nPbH,partIdx, xB1,yB1);
    if (!availableB1) logtrace(LogMotion,"spatial merging candidate B1: unavailable\n");
  }

  if (availableB1) {
    const PBMotion& b1 = img->get_mv_info(xB1,yB1);


    if (availableA1 && out_cand[idxA1] == b1) {
      idxB1 = idxA1;
      logtrace(LogMotion,"spatial merging candidate B1: redundant to A1\n");
    }
    else {
      idxB1 = computed_candidates++;
      out_cand[idxB1] = b1;

      logtrace(LogMotion,"spatial merging candidate B1:\n");
      logmvcand(out_cand[idxB1]);
    }
  }

  if (computed_candidates>=maxCandidates) return computed_candidates;


  int xB0 = xP+nPbW;
  int yB0 = yP-1;

  bool availableB0;
  int idxB0;

  if ((xP>>log2_parallel_merge_level) == (xB0>>log2_parallel_merge_level) &&
      (yP>>log2_parallel_merge_level) == (yB0>>log2_parallel_merge_level)) {
    availableB0 = false;
    logtrace(LogMotion,"spatial merging candidate B0: below parallel merge level\n");
  }
  else {
    availableB0 = img->available_pred_blk(xC,yC, nCS, xP,yP, nPbW,nPbH,partIdx, xB0,yB0);
    if (!availableB0) logtrace(LogMotion,"spatial merging candidate B0: unavailable\n");
  }

  if (availableB0) {
    const PBMotion& b0 = img->get_mv_info(xB0,yB0);


    if (availableB1 && out_cand[idxB1]==b0) {
      idxB0 = idxB1;
      logtrace(LogMotion,"spatial merging candidate B0: redundant to B1\n");
    }
    else {
      idxB0 = computed_candidates++;
      out_cand[idxB0] = b0;
      logtrace(LogMotion,"spatial merging candidate B0:\n");
      logmvcand(out_cand[idxB0]);
    }
  }

  if (computed_candidates>=maxCandidates) return computed_candidates;


  int xA0 = xP-1;
  int yA0 = yP+nPbH;

  bool availableA0;
  int idxA0;

  if ((xP>>log2_parallel_merge_level) == (xA0>>log2_parallel_merge_level) &&
      (yP>>log2_parallel_merge_level) == (yA0>>log2_parallel_merge_level)) {
    availableA0 = false;
    logtrace(LogMotion,"spatial merging candidate A0: below parallel merge level\n");
  }
  else {
    availableA0 = img->available_pred_blk(xC,yC, nCS, xP,yP, nPbW,nPbH,partIdx, xA0,yA0);
    if (!availableA0) logtrace(LogMotion,"spatial merging candidate A0: unavailable\n");
  }

  if (availableA0) {
    const PBMotion& a0 = img->get_mv_info(xA0,yA0);


    if (availableA1 && out_cand[idxA1]==a0) {
      idxA0 = idxA1;
      logtrace(LogMotion,"spatial merging candidate A0: redundant to A1\n");
    }
    else {
      idxA0 = computed_candidates++;
      out_cand[idxA0] = a0;
      logtrace(LogMotion,"spatial merging candidate A0:\n");
      logmvcand(out_cand[idxA0]);
    }
  }

  if (computed_candidates>=maxCandidates) return computed_candidates;


  int xB2 = xP-1;
  int yB2 = yP-1;

  bool availableB2;
  int idxB2;


  if (computed_candidates==4) {
    availableB2 = false;
    logtrace(LogMotion,"spatial merging candidate B2: ignore\n");
  }
  else if ((xP>>log2_parallel_merge_level) == (xB2>>log2_parallel_merge_level) &&
           (yP>>log2_parallel_merge_level) == (yB2>>log2_parallel_merge_level)) {
    availableB2 = false;
    logtrace(LogMotion,"spatial merging candidate B2: below parallel merge level\n");
  }
  else {
    availableB2 = img->available_pred_blk(xC,yC, nCS, xP,yP, nPbW,nPbH,partIdx, xB2,yB2);
    if (!availableB2) logtrace(LogMotion,"spatial merging candidate B2: unavailable\n");
  }

  if (availableB2) {
    const PBMotion& b2 = img->get_mv_info(xB2,yB2);


    if (availableB1 && out_cand[idxB1]==b2) {
      idxB2 = idxB1;
      logtrace(LogMotion,"spatial merging candidate B2: redundant to B1\n");
    }

    else if (availableA1 && out_cand[idxA1]==b2) {
      idxB2 = idxA1;
      logtrace(LogMotion,"spatial merging candidate B2: redundant to A1\n");
    }
    else {
      idxB2 = computed_candidates++;
      out_cand[idxB2] = b2;
      logtrace(LogMotion,"spatial merging candidate B2:\n");
      logmvcand(out_cand[idxB2]);
    }
  }

  return computed_candidates;
}
