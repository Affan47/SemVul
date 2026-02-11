ensQcsequenceMatch(const EnsPQcsequence qcs1,
                          const EnsPQcsequence qcs2)
{
    if (!qcs1)
        return ajFalse;

    if (!qcs2)
        return ajFalse;

    if (qcs1 == qcs2)
        return ajTrue;

    if (qcs1->Identifier != qcs2->Identifier)
        return ajFalse;

    if ((qcs1->Adaptor && qcs2->Adaptor) && (qcs1->Adaptor != qcs2->Adaptor))
        return ajFalse;

    if (!ensQcdatabaseMatch(qcs1->Qcdatabase, qcs2->Qcdatabase))
        return ajFalse;

    if (!ajStrMatchCaseS(qcs1->Name, qcs2->Name))
        return ajFalse;

    if (!ajStrMatchCaseS(qcs1->Accession, qcs2->Accession))
        return ajFalse;

    if (!ajStrMatchCaseS(qcs1->Description, qcs2->Description))
        return ajFalse;

    if (!ajStrMatchCaseS(qcs1->Type, qcs2->Type))
        return ajFalse;

    if (qcs1->Version != qcs2->Version)
        return ajFalse;

    if (qcs1->Length != qcs2->Length)
        return ajFalse;

    if (qcs1->CdsStart != qcs2->CdsStart)
        return ajFalse;

    if (qcs1->CdsEnd != qcs2->CdsEnd)
        return ajFalse;

    if (qcs1->CdsStrand != qcs2->CdsStrand)
        return ajFalse;

    if (qcs1->Polya != qcs2->Polya)
        return ajFalse;

    return ajTrue;
}
