void tipc_crypto_key_flush(struct tipc_crypto *c)
{
	struct tipc_crypto *tx, *rx;
	int k;

	spin_lock_bh(&c->lock);
	if (is_rx(c)) {

		rx = c;
		tx = tipc_net(rx->net)->crypto_tx;
		if (cancel_delayed_work(&rx->work)) {
			kfree(rx->skey);
			rx->skey = NULL;
			atomic_xchg(&rx->key_distr, 0);
			tipc_node_put(rx->node);
		}

		k = atomic_xchg(&rx->peer_rx_active, 0);
		if (k) {
			tipc_aead_users_dec(tx->aead[k], 0);

			tx->timer1 = jiffies;
		}
	}

	c->flags = 0;
	tipc_crypto_key_set_state(c, 0, 0, 0);
	for (k = KEY_MIN; k <= KEY_MAX; k++)
		tipc_crypto_key_detach(c->aead[k], &c->lock);
	atomic64_set(&c->sndnxt, 0);
	spin_unlock_bh(&c->lock);
}
