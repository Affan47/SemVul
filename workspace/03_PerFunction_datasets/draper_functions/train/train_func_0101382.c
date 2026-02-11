recogTrainUnlabelled(L_RECOG   *recog,
                     L_RECOG   *recogboot,
                     PIX       *pixs,
                     BOX       *box,
                     l_int32    singlechar,
                     l_float32  minscore,
                     l_int32    debug)
{
char      *text;
l_float32  score;
NUMA      *nascore, *na;
PIX       *pixc, *pixb, *pixdb;
PIXA      *pixa, *pixaf;

    PROCNAME("recogTrainUnlabelled");

    if (!recog)
        return ERROR_INT("recog not defined", procName, 1);
    if (!recogboot)
        return ERROR_INT("recogboot not defined", procName, 1);
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);


    if (box)
        pixc = pixClipRectangle(pixs, box, NULL);
    else
        pixc = pixClone(pixs);


    if (pixGetDepth(pixc) > 1)
        pixb = pixConvertTo1(pixc, recog->threshold);
    else
        pixb = pixClone(pixc);
    pixDestroy(&pixc);


    if (singlechar == 1) {
        if (!debug) {
            recogIdentifyPix(recogboot, pixb, NULL);
        } else {
            recogIdentifyPix(recogboot, pixb, &pixdb);
            pixaAddPix(recog->pixadb_boot, pixdb, L_INSERT);
        }
        rchExtract(recogboot->rch, NULL, &score, &text, NULL, NULL, NULL, NULL);


        pixaf = pixaCreate(1);
        if (score >= minscore) {
            pixSetText(pixb, text);
            pixaAddPix(pixaf, pixb, L_CLONE);
            FREE(text);


            if (debug && ((text = pixGetText(pixs)) != NULL))
                L_INFO("Testing: input pix has character label: %s\n",
                       procName, text);
        }
    } else {

        pixSplitIntoCharacters(pixb, 5, 5, NULL, &pixa, NULL);

        if (!debug) {
            recogIdentifyPixa(recogboot, pixa, NULL, NULL);
        } else {
            recogIdentifyPixa(recogboot, pixa, NULL, &pixdb);
            pixaAddPix(recog->pixadb_boot, pixdb, L_INSERT);
        }

        rchaExtract(recogboot->rcha, NULL, &nascore, NULL, NULL, NULL,
                    NULL, NULL);
        na = numaMakeThresholdIndicator(nascore, minscore, L_SELECT_IF_GTE);
        pixaf = pixaSelectWithIndicator(pixa, na, NULL);
        pixaDestroy(&pixa);
        numaDestroy(&nascore);
        numaDestroy(&na);
    }
    pixDestroy(&pixb);


    recogAddSamples(recog, pixaf, -1, debug);
    pixaDestroy(&pixaf);
    return 0;
}
