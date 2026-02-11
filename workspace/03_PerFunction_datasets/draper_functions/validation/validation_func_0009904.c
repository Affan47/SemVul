smb2_query_path_info(const unsigned int xid, struct cifs_tcon *tcon,
		     struct cifs_sb_info *cifs_sb, const char *full_path,
		     FILE_ALL_INFO *data, bool *adjust_tz, bool *symlink)
{
	int rc;
	struct smb2_file_all_info *smb2_data;

	*adjust_tz = false;
	*symlink = false;

	smb2_data = kzalloc(sizeof(struct smb2_file_all_info) + PATH_MAX * 2,
			    GFP_KERNEL);
	if (smb2_data == NULL)
		return -ENOMEM;

	rc = smb2_open_op_close(xid, tcon, cifs_sb, full_path,
				FILE_READ_ATTRIBUTES, FILE_OPEN, 0,
				smb2_data, SMB2_OP_QUERY_INFO);
	if (rc == -EOPNOTSUPP) {
		*symlink = true;

		rc = smb2_open_op_close(xid, tcon, cifs_sb, full_path,
					FILE_READ_ATTRIBUTES, FILE_OPEN,
					OPEN_REPARSE_POINT, smb2_data,
					SMB2_OP_QUERY_INFO);
	}
	if (rc)
		goto out;

	move_smb2_info_to_cifs(data, smb2_data);
out:
	kfree(smb2_data);
	return rc;
}
