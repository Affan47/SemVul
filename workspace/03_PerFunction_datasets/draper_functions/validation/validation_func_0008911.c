mbox_info_set_flags (CamelMessageInfo *mi,
                     guint32 flags,
                     guint32 set)
{

	if (((CamelMboxSummary *) mi->summary)->xstatus
	    && (flags & (CAMEL_MESSAGE_SEEN | CAMEL_MESSAGE_FLAGGED | CAMEL_MESSAGE_ANSWERED | CAMEL_MESSAGE_DELETED))) {
		flags |= CAMEL_MESSAGE_FOLDER_XEVCHANGE | CAMEL_MESSAGE_FOLDER_FLAGGED;
		set |= CAMEL_MESSAGE_FOLDER_XEVCHANGE | CAMEL_MESSAGE_FOLDER_FLAGGED;
	}

	return CAMEL_FOLDER_SUMMARY_CLASS (camel_mbox_summary_parent_class)->
		info_set_flags (mi, flags, set);
}
