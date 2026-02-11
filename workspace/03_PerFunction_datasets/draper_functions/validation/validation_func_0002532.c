EqRange (
    Obj                 listL,
    Obj                 listR )
{
    return ( GET_LEN_RANGE(listL) == GET_LEN_RANGE(listR)
          && GET_LOW_RANGE(listL) == GET_LOW_RANGE(listR)
          && GET_INC_RANGE(listL) == GET_INC_RANGE(listR) );
}
