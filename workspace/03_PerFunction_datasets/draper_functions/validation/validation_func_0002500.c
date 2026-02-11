totem_action_eject (TotemObject *totem)
{
	GMount *mount;

	mount = totem_get_mount_for_media (totem->mrl);
	if (mount == NULL)
		return;

	g_free (totem->mrl);
	totem->mrl = NULL;
	bacon_video_widget_close (totem->bvw);
	totem_file_closed (totem);
	totem->has_played_emitted = FALSE;


	g_mount_eject_with_operation (mount, G_MOUNT_UNMOUNT_NONE, NULL, NULL, NULL, NULL);
	g_object_unref (mount);
}
