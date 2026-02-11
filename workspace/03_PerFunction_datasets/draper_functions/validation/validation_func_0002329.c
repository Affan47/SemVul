queue_pollack(avmcard *card)
{
	struct sk_buff *skb;
	void *p;

	skb = alloc_skb(3, GFP_ATOMIC);
	if (!skb) {
		printk(KERN_CRIT "%s: no memory, lost poll ack\n",
		       card->name);
		return;
	}
	p = skb->data;
	_put_byte(&p, 0);
	_put_byte(&p, 0);
	_put_byte(&p, SEND_POLLACK);
	skb_put(skb, (u8 *)p - (u8 *)skb->data);

	b1dma_queue_tx(card, skb);
}
