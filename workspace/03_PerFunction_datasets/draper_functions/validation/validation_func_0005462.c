modify_share (OobsShare *new_share, OobsShare *old_share, OobsListIter *list_iter, GtkTreeIter *iter)
{
	OobsObject *old_config, *new_config;
	OobsList *old_list, *new_list;

	if (OOBS_IS_SHARE_SMB (old_share)) {
		old_config = GST_SHARES_TOOL (tool)->smb_config;
		old_list = oobs_smb_config_get_shares (OOBS_SMB_CONFIG (old_config));
	} else {
		old_config = GST_SHARES_TOOL (tool)->nfs_config;
		old_list = oobs_nfs_config_get_shares (OOBS_NFS_CONFIG (old_config));
	}

	oobs_list_remove (old_list, list_iter);


	if (OOBS_IS_SHARE_SMB (new_share)) {
		new_config = GST_SHARES_TOOL (tool)->smb_config;
		new_list = oobs_smb_config_get_shares (OOBS_SMB_CONFIG (new_config));
	} else {
		new_config = GST_SHARES_TOOL (tool)->nfs_config;
		new_list = oobs_nfs_config_get_shares (OOBS_NFS_CONFIG (new_config));
	}

	oobs_list_append (new_list, list_iter);
	oobs_list_set (new_list, list_iter, new_share);
	g_object_unref (new_share);

	table_modify_share_at_iter (iter, new_share, list_iter);

	gst_tool_commit (tool, new_config);

	if (old_config != new_config)
		gst_tool_commit (tool, old_config);
}
