PredictorSetupEncode(TIFF* tif)
{
        TIFFPredictorState* sp = PredictorState(tif);
        TIFFDirectory* td = &tif->tif_dir;

        if (!(*sp->setupencode)(tif) || !PredictorSetup(tif))
                return 0;

        if (sp->predictor == 2) {
                switch (td->td_bitspersample) {
                        case 8:  sp->pfunc = horDiff8; break;
                        case 16: sp->pfunc = horDiff16; break;
                }


                sp->coderow = tif->tif_encoderow;
                tif->tif_encoderow = PredictorEncodeRow;
                sp->codestrip = tif->tif_encodestrip;
                tif->tif_encodestrip = PredictorEncodeTile;
                sp->codetile = tif->tif_encodetile;
                tif->tif_encodetile = PredictorEncodeTile;
        }

        else if (sp->predictor == 3) {
                sp->pfunc = fpDiff;


                sp->coderow = tif->tif_encoderow;
                tif->tif_encoderow = PredictorEncodeRow;
                sp->codestrip = tif->tif_encodestrip;
                tif->tif_encodestrip = PredictorEncodeTile;
                sp->codetile = tif->tif_encodetile;
                tif->tif_encodetile = PredictorEncodeTile;
        }

        return 1;
}
