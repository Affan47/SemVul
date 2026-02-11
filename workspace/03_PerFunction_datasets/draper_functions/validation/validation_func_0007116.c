pppoe_create(struct net *net, struct socket *sock, int kern)
{
	struct sock *sk;

	sk = sk_alloc(net, PF_PPPOX, GFP_KERNEL, &pppoe_sk_proto, kern);
	if (!sk)
		return -ENOMEM;

	sock_init_data(sock, sk);

	sock->state	= SS_UNCONNECTED;
	sock->ops	= &pppoe_ops;

	sk->sk_backlog_rcv	= pppoe_rcv_core;
	sk->sk_state		= PPPOX_NONE;
	sk->sk_type		= SOCK_STREAM;
	sk->sk_family		= PF_PPPOX;
	sk->sk_protocol		= PX_PROTO_OE;

	INIT_WORK(&pppox_sk(sk)->proto.pppoe.padt_work,
		  pppoe_unbind_sock_work);

	return 0;
}
