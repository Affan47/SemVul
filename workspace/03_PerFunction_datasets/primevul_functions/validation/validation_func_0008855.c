int headerIsEntry(Header h, rpmTagVal tag)
{

    return (findEntry(h, tag, RPM_NULL_TYPE) ? 1 : 0);

}
