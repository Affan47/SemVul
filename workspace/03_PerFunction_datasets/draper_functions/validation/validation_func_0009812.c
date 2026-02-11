FDKaacEnc_finalizeIntensityDecision(const FIXP_DBL *hrrErr,
                                    INT            *isMask,
                                    const FIXP_DBL *realIsScale,
                                    const FIXP_DBL *normSfbLoudness,
                                    const INTENSITY_PARAMETERS *isParams,
                                    const INT       sfbCnt,
                                    const INT       sfbPerGroup,
                                    const INT       maxSfbPerGroup)
{
  INT sfb,sfboffs, j;
  INT startIsSfb = 0;
  INT inIsBlock;
  INT currentIsSfbCount;
  FIXP_DBL overallHrrError;
  FIXP_DBL isScaleLast = FL2FXCONST_DBL(0.0f);
  FIXP_DBL isRegionLoudness;

  for (sfboffs = 0; sfboffs < sfbCnt; sfboffs += sfbPerGroup) {
    inIsBlock = 0;
    currentIsSfbCount = 0;
    overallHrrError = FL2FXCONST_DBL(0.0f);
    isRegionLoudness = FL2FXCONST_DBL(0.0f);
    for (sfb = 0; sfb < maxSfbPerGroup; sfb++) {
      if (isMask[sfboffs + sfb] == 1) {
        if (currentIsSfbCount == 0) {
          startIsSfb = sfboffs + sfb;
          isScaleLast = realIsScale[sfboffs + sfb];
        }
        inIsBlock = 1;
        currentIsSfbCount++;
        overallHrrError  += hrrErr[sfboffs + sfb] >> (MAX_SFB_PER_GROUP_SF-3);
        isRegionLoudness += normSfbLoudness[sfboffs + sfb] >> MAX_SFB_PER_GROUP_SF;
      }
      else {


        if (inIsBlock) {
          overallHrrError  += hrrErr[sfboffs + sfb] >> (MAX_SFB_PER_GROUP_SF-3);
          isRegionLoudness += normSfbLoudness[sfboffs + sfb] >> MAX_SFB_PER_GROUP_SF;

          if ( (hrrErr[sfboffs + sfb] < (isParams->local_error_thresh>>3)) && (overallHrrError < (isParams->total_error_thresh>>MAX_SFB_PER_GROUP_SF)) ) {
            currentIsSfbCount++;

            isMask[sfboffs + sfb] = 1;
          } else {
            inIsBlock = 0;
          }
        }
      }

      if (inIsBlock) {
        if( fAbs(isScaleLast-realIsScale[sfboffs + sfb]) < (isParams->direction_deviation_thresh>>(REAL_SCALE_SF+LD_DATA_SHIFT-IS_DIRECTION_DEVIATION_THRESH_SF)) ) {
          isScaleLast = realIsScale[sfboffs + sfb];
        }
        else{
          isMask[sfboffs + sfb] = 0;
          inIsBlock = 0;
          currentIsSfbCount--;
        }
      }

      if (currentIsSfbCount > 0 && (!inIsBlock || sfb == maxSfbPerGroup - 1)) {

        if (currentIsSfbCount < isParams->min_is_sfbs || (isRegionLoudness < isParams->is_region_min_loudness>>MAX_SFB_PER_GROUP_SF)) {
          for(j = startIsSfb; j <= sfboffs + sfb; j++) {
            isMask[j] = 0;
          }
        }
        currentIsSfbCount = 0;
        overallHrrError = FL2FXCONST_DBL(0.0f);
        isRegionLoudness = FL2FXCONST_DBL(0.0f);
      }
    }
  }
}
