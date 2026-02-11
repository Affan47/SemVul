uid_reset_num(struct query *ctl)
{
    struct idlist *idp;
    for (idp = ctl->oldsaved; idp; idp = idp->next)
	idp->val.status.num = 0;
}
