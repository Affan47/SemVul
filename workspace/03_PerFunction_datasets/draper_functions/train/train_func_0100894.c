UT_go_set_file_permissions (char const *uri, UT_GOFilePermissions * file_permissions)
{
#if defined (GOFFICE_WITH_GNOME)
	GnomeVFSFileInfo *file_info;
	GnomeVFSResult result;

        file_info = gnome_vfs_file_info_new ();
	file_info->permissions = (GnomeVFSFilePermissions)0;


	if (file_permissions->owner_read == TRUE)
		file_info->permissions = (GnomeVFSFilePermissions)(file_info->permissions | GNOME_VFS_PERM_USER_READ);

	if (file_permissions->owner_write == TRUE)
		file_info->permissions = (GnomeVFSFilePermissions)(file_info->permissions | GNOME_VFS_PERM_USER_WRITE);

	if (file_permissions->owner_execute == TRUE)
		file_info->permissions = (GnomeVFSFilePermissions)(file_info->permissions | GNOME_VFS_PERM_USER_EXEC);


	if (file_permissions->group_read == TRUE)
		file_info->permissions = (GnomeVFSFilePermissions)(file_info->permissions | GNOME_VFS_PERM_GROUP_READ);

	if (file_permissions->group_write == TRUE)
		file_info->permissions = (GnomeVFSFilePermissions)(file_info->permissions | GNOME_VFS_PERM_GROUP_WRITE);

	if (file_permissions->group_execute == TRUE)
		file_info->permissions = (GnomeVFSFilePermissions)(file_info->permissions | GNOME_VFS_PERM_GROUP_EXEC);


	if (file_permissions->others_read == TRUE)
		file_info->permissions = (GnomeVFSFilePermissions)(file_info->permissions | GNOME_VFS_PERM_OTHER_READ);

	if (file_permissions->others_write == TRUE)
		file_info->permissions = (GnomeVFSFilePermissions)(file_info->permissions | GNOME_VFS_PERM_OTHER_WRITE);

	if (file_permissions->others_execute == TRUE)
		file_info->permissions = (GnomeVFSFilePermissions)(file_info->permissions | GNOME_VFS_PERM_OTHER_EXEC);

	result = gnome_vfs_set_file_info (uri, file_info,
					  (GnomeVFSSetFileInfoMask) (GNOME_VFS_FILE_INFO_GET_ACCESS_RIGHTS |
								    GNOME_VFS_FILE_INFO_FOLLOW_LINKS |
								    GNOME_VFS_SET_FILE_INFO_PERMISSIONS));

	if (result != GNOME_VFS_OK)
		g_warning ("Error setting permissions for '%s'.", uri);

	gnome_vfs_file_info_unref (file_info);
#elif ! defined (G_OS_WIN32)
	mode_t permissions = 0;
	int result;
	char *filename;


	if (file_permissions->owner_read == TRUE)
		permissions |= S_IRUSR;

	if (file_permissions->owner_write == TRUE)
		permissions |= S_IWUSR;

	if (file_permissions->owner_execute == TRUE)
		permissions |= S_IXUSR;


	if (file_permissions->group_read == TRUE)
		permissions |= S_IRGRP;

	if (file_permissions->group_write == TRUE)
		permissions |= S_IWGRP;

	if (file_permissions->group_execute == TRUE)
		permissions |= S_IXGRP;


	if (file_permissions->others_read == TRUE)
		permissions |= S_IROTH;

	if (file_permissions->others_write == TRUE)
		permissions |= S_IWOTH;

	if (file_permissions->others_execute == TRUE)
		permissions |= S_IXOTH;

	filename = UT_go_filename_from_uri (uri);

#ifdef HAVE_G_CHMOD
	result = g_chmod (filename, permissions);
#else
	result = chmod (filename, permissions);
#endif

	g_free (filename);

	if (result != 0)
		g_warning ("Error setting permissions for %s.", uri);
#endif
}
