ARTassignnumbers()
{
    register char	*p;
    register int	i;
    register NEWSGROUP	*ngp;

    p = &Xref.Data[Xref.Used];
    for (i = 0; (ngp = GroupPointers[i]) != NULL; i++) {


	if (ngp->PostCount > 0)
	    continue;


	ngp->PostCount++;
	ngp->Last++;
	if (!FormatLong(ngp->LastString, (long)ngp->Last, ngp->Lastwidth)) {
	    syslog(L_ERROR, "%s cant update_active %s", LogName, ngp->Name);
	    continue;
	}
	ngp->Filenum = ngp->Last;
	(void)sprintf(p, " %s:%lu", ngp->Name, ngp->Filenum);
	p += strlen(p);
    }
    Xref.Used = p - Xref.Data;
    Xref.Data[Xref.Used++] = '\n';
}
