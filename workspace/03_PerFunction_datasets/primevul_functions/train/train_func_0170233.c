int OTHERNAME_cmp(OTHERNAME *a, OTHERNAME *b)
{
    int result = -1;

    if (!a || !b)
        return -1;

    if ((result = OBJ_cmp(a->type_id, b->type_id)) != 0)
        return result;

    result = ASN1_TYPE_cmp(a->value, b->value);
    return result;
}
