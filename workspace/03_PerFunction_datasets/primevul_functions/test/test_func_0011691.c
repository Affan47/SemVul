static int selinux_file_open(struct file *file)
{
	struct file_security_struct *fsec;
	struct inode_security_struct *isec;

	fsec = selinux_file(file);
	isec = inode_security(file_inode(file));


	fsec->isid = isec->sid;
	fsec->pseqno = avc_policy_seqno(&selinux_state);


	return file_path_has_perm(file->f_cred, file, open_file_to_av(file));
}
