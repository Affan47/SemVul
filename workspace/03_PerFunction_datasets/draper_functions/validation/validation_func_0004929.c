vee_info_ptr (const CamelMessageInfo *mi,
              gint id)
{
	CamelVeeMessageInfo *vmi = (CamelVeeMessageInfo *) mi;
	CamelMessageInfo *rmi;
	gpointer p;

	rmi = camel_folder_summary_get (vmi->orig_summary, mi->uid + 8);
	HANDLE_NULL_INFO (NULL);
	p = (gpointer) camel_message_info_ptr (rmi, id);
	camel_message_info_free (rmi);

	return p;
}
