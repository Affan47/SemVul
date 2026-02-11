kaweth_usb_receive(struct urb *urb)
{
	struct device *dev = &urb->dev->dev;
	struct kaweth_device *kaweth = urb->context;
	struct net_device *net = kaweth->net;
	int status = urb->status;

	int count = urb->actual_length;
	int count2 = urb->transfer_buffer_length;

	__u16 pkt_len = le16_to_cpup((__le16 *)kaweth->rx_buf);

	struct sk_buff *skb;

	if (unlikely(status == -EPIPE)) {
		kaweth->stats.rx_errors++;
		kaweth->end = 1;
		wake_up(&kaweth->term_wait);
		dev_dbg(dev, "Status was -EPIPE.\n");
		return;
	}
	if (unlikely(status == -ECONNRESET || status == -ESHUTDOWN)) {

		kaweth->end = 1;
		wake_up(&kaweth->term_wait);
		dev_dbg(dev, "Status was -ECONNRESET or -ESHUTDOWN.\n");
		return;
	}
	if (unlikely(status == -EPROTO || status == -ETIME ||
		     status == -EILSEQ)) {
		kaweth->stats.rx_errors++;
		dev_dbg(dev, "Status was -EPROTO, -ETIME, or -EILSEQ.\n");
		return;
	}
	if (unlikely(status == -EOVERFLOW)) {
		kaweth->stats.rx_errors++;
		dev_dbg(dev, "Status was -EOVERFLOW.\n");
	}
	spin_lock(&kaweth->device_lock);
	if (IS_BLOCKED(kaweth->status)) {
		spin_unlock(&kaweth->device_lock);
		return;
	}
	spin_unlock(&kaweth->device_lock);

	if(status && status != -EREMOTEIO && count != 1) {
		dev_err(&kaweth->intf->dev,
			"%s RX status: %d count: %d packet_len: %d\n",
			net->name, status, count, (int)pkt_len);
		kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                return;
	}

	if(kaweth->net && (count > 2)) {
		if(pkt_len > (count - 2)) {
			dev_err(&kaweth->intf->dev,
				"Packet length too long for USB frame (pkt_len: %x, count: %x)\n",
				pkt_len, count);
			dev_err(&kaweth->intf->dev, "Packet len & 2047: %x\n",
				pkt_len & 2047);
			dev_err(&kaweth->intf->dev, "Count 2: %x\n", count2);
		        kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                        return;
                }

		if(!(skb = dev_alloc_skb(pkt_len+2))) {
		        kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                        return;
		}

		skb_reserve(skb, 2);

		skb_copy_to_linear_data(skb, kaweth->rx_buf + 2, pkt_len);

		skb_put(skb, pkt_len);

		skb->protocol = eth_type_trans(skb, net);

		netif_rx(skb);

		kaweth->stats.rx_packets++;
		kaweth->stats.rx_bytes += pkt_len;
	}

	kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
}
