libipw_rx_frame_decrypt_msdu(struct libipw_device *ieee,
				struct sk_buff *skb, int keyidx,
				struct lib80211_crypt_data *crypt)
{
	struct libipw_hdr_3addr *hdr;
	int res, hdrlen;

	if (crypt == NULL || crypt->ops->decrypt_msdu == NULL)
		return 0;

	hdr = (struct libipw_hdr_3addr *)skb->data;
	hdrlen = libipw_get_hdrlen(le16_to_cpu(hdr->frame_ctl));

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_msdu(skb, keyidx, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	if (res < 0) {
		printk(KERN_DEBUG "%s: MSDU decryption/MIC verification failed"
		       " (SA=%pM keyidx=%d)\n", ieee->dev->name, hdr->addr2,
		       keyidx);
		return -1;
	}

	return 0;
}
