Put32u(void * Value, unsigned PutValue)
{
    if (MotorolaOrder){
        ((uchar *)Value)[0] = (uchar)(PutValue>>24);
        ((uchar *)Value)[1] = (uchar)(PutValue>>16);
        ((uchar *)Value)[2] = (uchar)(PutValue>>8);
        ((uchar *)Value)[3] = (uchar)PutValue;
    }else{
        ((uchar *)Value)[0] = (uchar)PutValue;
        ((uchar *)Value)[1] = (uchar)(PutValue>>8);
        ((uchar *)Value)[2] = (uchar)(PutValue>>16);
        ((uchar *)Value)[3] = (uchar)(PutValue>>24);
    }
}
