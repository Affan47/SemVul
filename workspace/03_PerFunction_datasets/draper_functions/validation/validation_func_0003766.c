mkvect0(len)
unsigned int len;
{
    struct vector *ptr;
    truc *vec;
    truc obj;
    unsigned int k;

    k = SIZEOFVECTOR(len);
    obj = newobj(fVECTOR,k,(trucptr *)&ptr);

    ptr->flag = fVECTOR;
    ptr->flg2 = 0;
    ptr->len = len;
    vec = (truc *)&(ptr->ele0);
    while(--k)
        *vec++ = zero;
    return(obj);
}
