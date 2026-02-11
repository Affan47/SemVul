adjust_index(IV index, IV base)
{
 if (index >= base || index > -1) return index-base;
 return index;
}
