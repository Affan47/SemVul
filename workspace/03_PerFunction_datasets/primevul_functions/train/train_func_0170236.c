static int edipartyname_cmp(const EDIPARTYNAME *a, const EDIPARTYNAME *b)
{
    int res;

    if (a == NULL || b == NULL) {


        return -1;
    }
    if (a->nameAssigner == NULL && b->nameAssigner != NULL)
        return -1;
    if (a->nameAssigner != NULL && b->nameAssigner == NULL)
        return 1;

    if (a->nameAssigner != NULL) {
        res = ASN1_STRING_cmp(a->nameAssigner, b->nameAssigner);
        if (res != 0)
            return res;
    }


    if (a->partyName == NULL || b->partyName == NULL)
        return -1;

    return ASN1_STRING_cmp(a->partyName, b->partyName);
}
