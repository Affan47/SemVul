AVCE00GenEndSection(AVCE00GenInfo *psInfo, AVCFileType eType,
                                GBool bCont)
{
    if (bCont == FALSE)
    {


        AVCE00GenReset(psInfo);
        psInfo->iCurItem = 0;

        if (eType == AVCFileARC ||
            eType == AVCFilePAL ||
            eType == AVCFileRPL ||
            eType == AVCFileCNT ||
            eType == AVCFileTOL ||
            eType == AVCFileTXT ||
            eType == AVCFileTX6 )
        {
            sprintf(psInfo->pszBuf,
    "        -1         0         0         0         0         0         0");
        }
        else if (eType == AVCFileLAB)
        {
            if (psInfo->nPrecision == AVC_DOUBLE_PREC)
                sprintf(psInfo->pszBuf,
          "        -1         0 0.00000000000000E+00 0.00000000000000E+00");
            else
                sprintf(psInfo->pszBuf,
          "        -1         0 0.0000000E+00 0.0000000E+00");
        }
        else if (eType == AVCFilePRJ)
        {
            sprintf(psInfo->pszBuf, "EOP");
        }
        else if (eType == AVCFileRXP )
        {
            sprintf(psInfo->pszBuf,"        -1         0");
        }
        else
        {
            CPLError(CE_Failure, CPLE_NotSupported,
                     "Unsupported E00 section type!");
            return NULL;
        }
    }
    else if ( psInfo->iCurItem == 0 &&
              psInfo->nPrecision == AVC_DOUBLE_PREC &&
              (eType == AVCFilePAL || eType == AVCFileRPL)     )
    {


        sprintf(psInfo->pszBuf,
                " 0.00000000000000E+00 0.00000000000000E+00");

        psInfo->iCurItem++;
    }
    else
    {


        return NULL;
    }

    return psInfo->pszBuf;
}
