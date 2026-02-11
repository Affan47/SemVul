pdf_event_issue_launch_url(pdf_document *doc, char *url, int new_frame)
{
	if (doc->event_cb)
	{
		fz_launch_url_event_internal e;

		e.base.type = FZ_DOCUMENT_EVENT_LAUNCH_URL;
		e.launch_url.url = url;
		e.launch_url.new_frame = new_frame;
		doc->event_cb((fz_doc_event *)&e, doc->event_cb_data);
	}
}
