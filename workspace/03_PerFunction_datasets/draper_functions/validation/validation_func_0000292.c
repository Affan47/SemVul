IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("SynchParams");
    prc->writeParamHex("flags", fSynchFlags);
    prc->endTag();

    unsigned int i;
    prc->writeTagNoBreak("ExcludePersistentStates");
    for (i=0; i<fSDLExcludeList.getSize(); i++)
        prc->getStream()->writeStr(fSDLExcludeList[i] + " ");
    prc->closeTagNoBreak();

    prc->writeTagNoBreak("VolatileStates");
    for (i=0; i<fSDLVolatileList.getSize(); i++)
        prc->getStream()->writeStr(fSDLVolatileList[i] + " ");
    prc->closeTagNoBreak();

    prc->closeTag();
}
