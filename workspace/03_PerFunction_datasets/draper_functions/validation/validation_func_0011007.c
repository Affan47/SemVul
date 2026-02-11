PickBestUV(VP8EncIterator* const it, VP8ModeScore* const rd) {
  const VP8Encoder* const enc = it->enc_;
  const VP8SegmentInfo* const dqm = &enc->dqm_[it->mb_->segment_];
  const int lambda = dqm->lambda_uv_;
  const uint8_t* const src = it->yuv_in_ + U_OFF;
  uint8_t* const tmp_dst = it->yuv_out2_ + U_OFF;
  uint8_t* const dst0 = it->yuv_out_ + U_OFF;
  VP8ModeScore rd_best;
  int mode;

  rd->mode_uv = -1;
  InitScore(&rd_best);
  for (mode = 0; mode < NUM_PRED_MODES; ++mode) {
    VP8ModeScore rd_uv;


    rd_uv.nz = ReconstructUV(it, &rd_uv, tmp_dst, mode);


    rd_uv.D  = VP8SSE16x8(src, tmp_dst);
    rd_uv.SD = 0;
    rd_uv.R  = VP8GetCostUV(it, &rd_uv);
    rd_uv.R += VP8FixedCostsUV[mode];

    SetRDScore(lambda, &rd_uv);
    if (mode == 0 || rd_uv.score < rd_best.score) {
      CopyScore(&rd_best, &rd_uv);
      rd->mode_uv = mode;
      memcpy(rd->uv_levels, rd_uv.uv_levels, sizeof(rd->uv_levels));
      memcpy(dst0, tmp_dst, UV_SIZE);
    }
  }
  VP8SetIntraUVMode(it, rd->mode_uv);
  AddScore(rd, &rd_best);
}
