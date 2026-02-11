id_find(struct idlist **idl, long number)
{
    struct idlist	*idp;
    for (idp = *idl; idp; idp = idp->next)
	if (idp->val.status.num == number)
	    return(idp);
    return(0);
}
