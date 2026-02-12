static int selinux_file_open(struct file *file, const struct cred *cred)
{
	struct file_security_struct *fsec;
	struct inode_security_struct *isec;

	fsec = file->f_security;
	isec = file_inode(file)->i_security;


	fsec->isid = isec->sid;
	fsec->pseqno = avc_policy_seqno();


	return file_path_has_perm(cred, file, open_file_to_av(file));
}
