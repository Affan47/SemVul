rtw_free_recvframe_queue(struct __queue *pframequeue,  struct __queue *pfree_recv_queue)
{
	struct recv_frame *hdr;
	struct list_head *plist, *phead;

	spin_lock(&pframequeue->lock);

	phead = get_list_head(pframequeue);
	plist = phead->next;

	while (phead != plist) {
		hdr = container_of(plist, struct recv_frame, list);

		plist = plist->next;

		rtw_free_recvframe((struct recv_frame *)hdr, pfree_recv_queue);
	}

	spin_unlock(&pframequeue->lock);

}
