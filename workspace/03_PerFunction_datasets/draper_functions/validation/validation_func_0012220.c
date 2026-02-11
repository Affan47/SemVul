mbox_summary_add (CamelLocalSummary *cls,
                  CamelMimeMessage *msg,
                  const CamelMessageInfo *info,
                  CamelFolderChangeInfo *ci,
                  GError **error)
{
	CamelLocalSummaryClass *local_summary_class;
	CamelMboxMessageInfo *mi;


	local_summary_class = CAMEL_LOCAL_SUMMARY_CLASS (camel_mbox_summary_parent_class);
	mi = (CamelMboxMessageInfo *) local_summary_class->add (
		cls, msg, info, ci, error);
	if (mi && ((CamelMboxSummary *) cls)->xstatus) {
		gchar status[8];


		encode_status (mi->info.info.flags & STATUS_STATUS, status);
		camel_medium_set_header ((CamelMedium *) msg, "Status", status);
		encode_status (mi->info.info.flags & STATUS_XSTATUS, status);
		camel_medium_set_header ((CamelMedium *) msg, "X-Status", status);
	}

	return (CamelMessageInfo *) mi;
}
