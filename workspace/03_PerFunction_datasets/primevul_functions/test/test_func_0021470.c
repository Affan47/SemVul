static void tipc_crypto_key_synch(struct tipc_crypto *rx, struct sk_buff *skb)
{
	struct tipc_ehdr *ehdr = (struct tipc_ehdr *)skb_network_header(skb);
	struct tipc_crypto *tx = tipc_net(rx->net)->crypto_tx;
	struct tipc_msg *hdr = buf_msg(skb);
	u32 self = tipc_own_addr(rx->net);
	u8 cur, new;
	unsigned long delay;


	rx->key_master = ehdr->master_key;
	if (!rx->key_master)
		tx->legacy_user = 1;


	if (!ehdr->destined || msg_short(hdr) || msg_destnode(hdr) != self)
		return;


	if (ehdr->rx_nokey) {

		tx->timer2 = jiffies;

		if (tx->key.keys &&
		    !atomic_cmpxchg(&rx->key_distr, 0, KEY_DISTR_SCHED)) {
			get_random_bytes(&delay, 2);
			delay %= 5;
			delay = msecs_to_jiffies(500 * ++delay);
			if (queue_delayed_work(tx->wq, &rx->work, delay))
				tipc_node_get(rx->node);
		}
	} else {

		atomic_xchg(&rx->key_distr, 0);
	}


	cur = atomic_read(&rx->peer_rx_active);
	new = ehdr->rx_key_active;
	if (tx->key.keys &&
	    cur != new &&
	    atomic_cmpxchg(&rx->peer_rx_active, cur, new) == cur) {
		if (new)
			tipc_aead_users_inc(tx->aead[new], INT_MAX);
		if (cur)
			tipc_aead_users_dec(tx->aead[cur], 0);

		atomic64_set(&rx->sndnxt, 0);

		tx->timer1 = jiffies;

		pr_debug("%s: key users changed %d-- %d++, peer %s\n",
			 tx->name, cur, new, rx->name);
	}
}
