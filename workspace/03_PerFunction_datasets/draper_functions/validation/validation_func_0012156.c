nfs4_exclusive_attrset(struct nfs4_opendata *opendata,
				struct iattr *sattr, struct nfs4_label **label)
{
	const u32 *attrset = opendata->o_res.attrset;

	if ((attrset[1] & FATTR4_WORD1_TIME_ACCESS) &&
	    !(sattr->ia_valid & ATTR_ATIME_SET))
		sattr->ia_valid |= ATTR_ATIME;

	if ((attrset[1] & FATTR4_WORD1_TIME_MODIFY) &&
	    !(sattr->ia_valid & ATTR_MTIME_SET))
		sattr->ia_valid |= ATTR_MTIME;


	if (opendata->o_arg.createmode != NFS4_CREATE_EXCLUSIVE &&
		attrset[1] & FATTR4_WORD1_MODE)
		sattr->ia_valid &= ~ATTR_MODE;

	if (attrset[2] & FATTR4_WORD2_SECURITY_LABEL)
		*label = NULL;
}
