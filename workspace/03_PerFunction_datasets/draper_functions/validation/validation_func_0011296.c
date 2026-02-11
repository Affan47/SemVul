camel_vee_message_info_data_new (CamelVeeSubfolderData *subfolder_data,
                                 const gchar *orig_message_uid)
{
	CamelVeeMessageInfoData *data;
	gchar *vee_message_uid;

	g_return_val_if_fail (CAMEL_IS_VEE_SUBFOLDER_DATA (subfolder_data), NULL);
	g_return_val_if_fail (orig_message_uid != NULL, NULL);

	data = g_object_new (CAMEL_TYPE_VEE_MESSAGE_INFO_DATA, NULL);
	data->priv->subfolder_data = g_object_ref (subfolder_data);

	vee_message_uid = g_strconcat (camel_vee_subfolder_data_get_folder_id (subfolder_data), orig_message_uid, NULL);

	data->priv->orig_message_uid = camel_pstring_strdup (orig_message_uid);
	data->priv->vee_message_uid = camel_pstring_add (vee_message_uid, TRUE);

	return data;
}
