static int econet_recvmsg(struct kiocb *iocb, struct socket *sock,
			  struct msghdr *msg, size_t len, int flags)
{
	struct sock *sk = sock->sk;
	struct sk_buff *skb;
	size_t copied;
	int err;

	msg->msg_namelen = sizeof(struct sockaddr_ec);

	mutex_lock(&econet_mutex);


	skb=skb_recv_datagram(sk,flags,flags&MSG_DONTWAIT,&err);


	if(skb==NULL)
		goto out;


	copied = skb->len;
	if (copied > len)
	{
		copied=len;
		msg->msg_flags|=MSG_TRUNC;
	}


	err = memcpy_toiovec(msg->msg_iov, skb->data, copied);
	if (err)
		goto out_free;
	sk->sk_stamp = skb->tstamp;

	if (msg->msg_name)
		memcpy(msg->msg_name, skb->cb, msg->msg_namelen);


	err = copied;

out_free:
	skb_free_datagram(sk, skb);
out:
	mutex_unlock(&econet_mutex);
	return err;
}
