messageview_destroy(MessageView *messageview)
{
	debug_print("destroy messageview\n");
	messageview_list = g_list_remove(messageview_list, messageview);

	if (messageview->mainwin->summaryview->messageview == messageview) {
		messageview->mainwin->summaryview->displayed = NULL;
		messageview->mainwin->summaryview->messageview = NULL;
	}
	if (messageview->mainwin->summaryview->ext_messageview == messageview) {
		messageview->mainwin->summaryview->displayed = NULL;
		messageview->mainwin->summaryview->ext_messageview = NULL;
	}
	if (!messageview->deferred_destroy)
		hooks_unregister_hook(MSGINFO_UPDATE_HOOKLIST,
			      messageview->msginfo_update_callback_id);

	if (messageview->updating) {
		debug_print("uh oh, better not touch that now (fetching)\n");
		messageview->deferred_destroy = TRUE;
		gtk_widget_hide(messageview->window);
		return;
	}

	if (messageview->mimeview->textview
	&&  messageview->mimeview->textview->loading) {
		debug_print("uh oh, better not touch that now (loading text)\n");
		messageview->deferred_destroy = TRUE;
		messageview->mimeview->textview->stop_loading = TRUE;
		gtk_widget_hide(messageview->window);
		return;
	}

	headerview_destroy(messageview->headerview);
	mimeview_destroy(messageview->mimeview);
	noticeview_destroy(messageview->noticeview);

	procmsg_msginfo_free(messageview->msginfo);
	toolbar_clear_list(TOOLBAR_MSGVIEW);
	if (messageview->toolbar) {
		toolbar_destroy(messageview->toolbar);
		g_free(messageview->toolbar);
	}

	list_free_strings(messageview->trail);
	g_list_free(messageview->trail);
	msgview_list = g_list_remove(msgview_list, messageview);

	if (messageview->window)
		gtk_widget_destroy(messageview->window);
	g_free(messageview);
}
