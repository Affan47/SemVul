ajFeatGetFlags(const AjPFeature thys,  AjPStr* Pflagstr)
{
    ajStrAssignC(Pflagstr, "");

    if(thys->Flags & AJFEATFLAG_START_BEFORE_SEQ)
        ajStrAppendC(Pflagstr, "<start ");
    if(thys->Flags & AJFEATFLAG_END_AFTER_SEQ)
        ajStrAppendC(Pflagstr, ">end ");
    if(thys->Flags & AJFEATFLAG_BETWEEN_SEQ)
        ajStrAppendC(Pflagstr, "x^y ");
    if(thys->Flags & AJFEATFLAG_START_TWO)
        ajStrAppendC(Pflagstr, "startrange ");
    if(thys->Flags & AJFEATFLAG_END_TWO)
        ajStrAppendC(Pflagstr, "endrange ");
    if(thys->Flags & AJFEATFLAG_POINT)
        ajStrAppendC(Pflagstr, "single-base ");
    if(thys->Flags & AJFEATFLAG_COMPLEMENT_MAIN)
        ajStrAppendC(Pflagstr, "complement(join) ");
    if(thys->Flags & AJFEATFLAG_MULTIPLE)
        ajStrAppendC(Pflagstr, "multiple ");
    if(thys->Flags & AJFEATFLAG_GROUP)
        ajStrAppendC(Pflagstr, "group ");
    if(thys->Flags & AJFEATFLAG_ORDER)
        ajStrAppendC(Pflagstr, "order ");
    if(thys->Flags & AJFEATFLAG_ONEOF)
        ajStrAppendC(Pflagstr, "oneof ");
    if(thys->Flags & AJFEATFLAG_REMOTEID)
        ajStrAppendC(Pflagstr, "remoteid ");
    if(thys->Flags & AJFEATFLAG_LABEL)
        ajStrAppendC(Pflagstr, "LABEL ");
    if(thys->Flags & AJFEATFLAG_START_UNSURE)
        ajStrAppendC(Pflagstr, "start-unsure ");
    if(thys->Flags & AJFEATFLAG_END_UNSURE)
        ajStrAppendC(Pflagstr, "end-unsure ");

    ajStrTrimWhite(Pflagstr);

    return ajTrue;
}
