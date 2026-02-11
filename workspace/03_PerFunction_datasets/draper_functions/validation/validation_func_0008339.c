ensSequenceeditApplyString(const EnsPSequenceedit se,
                                  ajint offset,
                                  AjPStr *Psequence)
{
    ajlong pos1 = 0;
    ajlong pos2 = 0;

    if (!se)
        return ajFalse;

    if (!Psequence)
        return ajFalse;

    if (!*Psequence)
        return ajFalse;

    pos1 = se->Start - offset;
    pos2 = se->End   - offset;

    if (pos2 < 1)
    {
        ajDebug("ensSequenceeditApplyString got an Ensembl Sequence Edit, "
                "which end position (%d) corrected for the offset (%d) lies "
                "beyond the sequence start (1).",
                se->End, offset);

        return ajFalse;
    }

    if (pos1 > (ajlong) ajStrGetLen(*Psequence))
    {
        ajDebug("ensSequenceeditApplyString got an Ensembl Sequence Edit, "
                "which start position (%d) corrected for the offset (%d) lies "
                "beyond the sequence end (%lu).",
                se->Start, offset, ajStrGetLen(*Psequence));


        return ajFalse;
    }


    ajStrCutRange(Psequence, pos1 - 1, pos2 - 1);

    ajStrInsertS(Psequence, pos1 - 1, se->Sequence);

    return ajTrue;
}
