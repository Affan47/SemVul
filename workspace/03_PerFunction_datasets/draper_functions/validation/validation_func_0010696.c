FDKaacEnc_TnsSync(
             TNS_DATA *tnsDataDest,
             const TNS_DATA *tnsDataSrc,
             TNS_INFO *tnsInfoDest,
             TNS_INFO *tnsInfoSrc,
             const INT blockTypeDest,
             const INT blockTypeSrc,
             const TNS_CONFIG *tC
             )
{
  int i, w, absDiff, nWindows;
  TNS_SUBBLOCK_INFO *sbInfoDest;
  const TNS_SUBBLOCK_INFO *sbInfoSrc;


  if ( (blockTypeSrc == SHORT_WINDOW && blockTypeDest != SHORT_WINDOW) ||
       (blockTypeDest == SHORT_WINDOW && blockTypeSrc != SHORT_WINDOW) )
  {
    return;
  }

  if (blockTypeDest != SHORT_WINDOW) {
    sbInfoDest = &tnsDataDest->dataRaw.Long.subBlockInfo;
    sbInfoSrc  = &tnsDataSrc->dataRaw.Long.subBlockInfo;
    nWindows   = 1;
  } else {
    sbInfoDest = &tnsDataDest->dataRaw.Short.subBlockInfo[0];
    sbInfoSrc  = &tnsDataSrc->dataRaw.Short.subBlockInfo[0];
    nWindows   = 8;
  }

  for (w=0; w<nWindows; w++) {
      const TNS_SUBBLOCK_INFO *pSbInfoSrcW  = sbInfoSrc  + w;
      TNS_SUBBLOCK_INFO       *pSbInfoDestW = sbInfoDest + w;
      INT doSync = 1, absDiffSum = 0;


      if (pSbInfoDestW->tnsActive || pSbInfoSrcW->tnsActive) {
        for (i = 0; i < tC->maxOrder; i++) {
          absDiff = FDKabs(tnsInfoDest->coef[w][HIFILT][i] - tnsInfoSrc->coef[w][HIFILT][i]);
          absDiffSum += absDiff;

          if ((absDiff > 1) || (absDiffSum > 2)) {
            doSync = 0;
            break;
          }
        }

        if (doSync) {

            if (pSbInfoSrcW->tnsActive) {

              if ((!pSbInfoDestW->tnsActive) ||
                  ((pSbInfoDestW->tnsActive) && (tnsInfoDest->numOfFilters[w] > tnsInfoSrc->numOfFilters[w])))
              {
                pSbInfoDestW->tnsActive = tnsInfoDest->numOfFilters[w] = 1;
              }
              tnsDataDest->filtersMerged = tnsDataSrc->filtersMerged;
              tnsInfoDest->order       [w][HIFILT] = tnsInfoSrc->order       [w][HIFILT];
              tnsInfoDest->length      [w][HIFILT] = tnsInfoSrc->length      [w][HIFILT];
              tnsInfoDest->direction   [w][HIFILT] = tnsInfoSrc->direction   [w][HIFILT];
              tnsInfoDest->coefCompress[w][HIFILT] = tnsInfoSrc->coefCompress[w][HIFILT];

              for (i = 0; i < tC->maxOrder; i++) {
                tnsInfoDest->coef[w][HIFILT][i] = tnsInfoSrc->coef[w][HIFILT][i];
              }
            }
            else
              pSbInfoDestW->tnsActive = tnsInfoDest->numOfFilters[w] = 0;
            }
        }

    }
}
