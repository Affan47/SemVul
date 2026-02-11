r8711_wx_get_scan(struct net_device *dev,
				struct iw_request_info *a,
				union iwreq_data *wrqu, char *extra)
{
	struct _adapter *padapter = netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct  __queue *queue = &pmlmepriv->scanned_queue;
	struct wlan_network *pnetwork = NULL;
	unsigned long irqL;
	struct list_head *plist, *phead;
	char *ev = extra;
	char *stop = ev + wrqu->data.length;
	u32 ret = 0, cnt = 0;

	if (padapter->bDriverStopped)
		return -EINVAL;
	while (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY |
			     _FW_UNDER_LINKING)) {
		msleep(30);
		cnt++;
		if (cnt > 100)
			break;
	}
	spin_lock_irqsave(&queue->lock, irqL);
	phead = &queue->queue;
	plist = phead->next;
	while (1) {
		if (end_of_queue_search(phead, plist))
			break;
		if ((stop - ev) < SCAN_ITEM_SIZE) {
			ret = -E2BIG;
			break;
		}
		pnetwork = LIST_CONTAINOR(plist, struct wlan_network, list);
		ev = translate_scan(padapter, a, pnetwork, ev, stop);
		plist = plist->next;
	}
	spin_unlock_irqrestore(&queue->lock, irqL);
	wrqu->data.length = ev - extra;
	wrqu->data.flags = 0;
	return ret;
}
