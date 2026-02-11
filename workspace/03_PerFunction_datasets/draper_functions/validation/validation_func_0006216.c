camel_imapx_list_response_get_summary_flags (CamelIMAPXListResponse *response)
{
	CamelStoreInfoFlags store_info_flags = 0;
	const gchar *flag;

	g_return_val_if_fail (CAMEL_IS_IMAPX_LIST_RESPONSE (response), 0);

	flag = CAMEL_IMAPX_LIST_ATTR_NOSELECT;
	if (camel_imapx_list_response_has_attribute (response, flag))
		store_info_flags |= CAMEL_STORE_INFO_FOLDER_NOSELECT;

	flag = CAMEL_IMAPX_LIST_ATTR_NOINFERIORS;
	if (camel_imapx_list_response_has_attribute (response, flag))
		store_info_flags |= CAMEL_STORE_INFO_FOLDER_NOINFERIORS;

	flag = CAMEL_IMAPX_LIST_ATTR_HASCHILDREN;
	if (camel_imapx_list_response_has_attribute (response, flag))
		store_info_flags |= CAMEL_STORE_INFO_FOLDER_CHILDREN;

	flag = CAMEL_IMAPX_LIST_ATTR_HASNOCHILDREN;
	if (camel_imapx_list_response_has_attribute (response, flag))
		store_info_flags |= CAMEL_STORE_INFO_FOLDER_NOCHILDREN;

	flag = CAMEL_IMAPX_LIST_ATTR_SUBSCRIBED;
	if (camel_imapx_list_response_has_attribute (response, flag))
		store_info_flags |= CAMEL_STORE_INFO_FOLDER_SUBSCRIBED;


	return store_info_flags;
}
