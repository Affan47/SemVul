LPCOLESTR Parser::FormatPropertyString(LPCOLESTR propertyString, ParseNodePtr pNode, uint32 *fullNameHintLength, uint32 *pShortNameOffset)
{


    OpCode op = pNode->nop;
    LPCOLESTR rightNode = nullptr;
    if (propertyString == nullptr)
    {
        propertyString = _u("");
    }

    if (op != knopInt && op != knopFlt && op != knopName && op != knopStr)
    {
        rightNode = _u("");
    }
    else if (op == knopStr)
    {
        return AppendNameHints(propertyString, pNode->sxPid.pid, fullNameHintLength, pShortNameOffset, false, true);
    }
    else if(op == knopFlt)
    {
        rightNode = m_pscan->StringFromDbl(pNode->sxFlt.dbl);
    }
    else
    {
        rightNode = op == knopInt ? m_pscan->StringFromLong(pNode->sxInt.lw)
            : pNode->sxPid.pid->Psz();
    }

    return AppendNameHints(propertyString, rightNode, fullNameHintLength, pShortNameOffset, false, true);
}
