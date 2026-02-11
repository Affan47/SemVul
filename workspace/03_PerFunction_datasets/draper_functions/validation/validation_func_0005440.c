IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    if (fFlags[kHasProxy] && fProxy == NULL)
        fFlags[kHasProxy] = false;
    prc->startTag("ControlParams");
    prc->writeParam("TagID", fTagID);
    prc->writeParam("Visible", fVisible);
    prc->endTag(true);

    prc->writeSimpleTag("Handler");
    pfGUICtrlProcWriteableObject::PrcWrite(prc, fHandler);
    prc->closeTag();

    prc->writeSimpleTag("DynTextLayer");
    fDynTextLayer->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("DynTextMap");
    fDynTextMap->prcWrite(prc);
    prc->closeTag();

    if (fColorScheme != NULL) {
        fColorScheme->prcWrite(prc);
    } else {
        prc->startTag("pfGUIColorScheme");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    prc->writeSimpleTag("SoundIndices");
    for (size_t i=0; i<fSoundIndices.getSize(); i++) {
        prc->startTag("SoundIndex");
        prc->writeParam("value", fSoundIndices[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    if (fFlags[kHasProxy]) {
        prc->writeSimpleTag("Proxy");
        fProxy->prcWrite(prc);
        prc->closeTag();
    }
    prc->writeSimpleTag("Skin");
    fSkin->prcWrite(prc);
    prc->closeTag();
}
