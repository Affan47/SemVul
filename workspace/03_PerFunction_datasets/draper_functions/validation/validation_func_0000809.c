sbrDecoder_drcInitChannel (
    HANDLE_SBR_DRC_CHANNEL  hDrcData )
{
  int band;

  if (hDrcData == NULL) {
    return;
  }

  for (band = 0; band < (64); band++) {
    hDrcData->prevFact_mag[band] = FL2FXCONST_DBL(0.5f);
  }

  for (band = 0; band < SBRDEC_MAX_DRC_BANDS; band++) {
    hDrcData->currFact_mag[band] = FL2FXCONST_DBL(0.5f);
    hDrcData->nextFact_mag[band] = FL2FXCONST_DBL(0.5f);
  }

  hDrcData->prevFact_exp = 1;
  hDrcData->currFact_exp = 1;
  hDrcData->nextFact_exp = 1;

  hDrcData->numBandsCurr = 0;
  hDrcData->numBandsNext = 0;

  hDrcData->winSequenceCurr = 0;
  hDrcData->winSequenceNext = 0;

  hDrcData->drcInterpolationSchemeCurr = 0;
  hDrcData->drcInterpolationSchemeNext = 0;

  hDrcData->enable = 0;
}
