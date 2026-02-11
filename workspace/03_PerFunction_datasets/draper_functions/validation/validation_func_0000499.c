request_unqueued (SoupSession *session, SoupMessage *msg,
		  gpointer data)
{
	if (msg->status_code == SOUP_STATUS_CANCELLED)
		cancelled_requests++;
}
