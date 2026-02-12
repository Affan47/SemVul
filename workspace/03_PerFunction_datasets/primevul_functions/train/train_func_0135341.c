_XimGetNestedListSeparator(
    XIMResourceList	 res_list,
    unsigned int	 res_num)
{
    return  _XimGetResourceListRec(res_list, res_num, XNSeparatorofNestedList);
}
