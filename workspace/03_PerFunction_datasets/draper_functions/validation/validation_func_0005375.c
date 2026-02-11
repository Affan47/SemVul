rb_ssl_tryconn_cb(rb_fde_t *F, void *data)
{
	struct ssl_connect *sconn = data;
	int ret;

	ret = do_ssl_handshake(F, rb_ssl_tryconn_cb, (void *)sconn);

	switch (ret)
	{
	case -1:
		rb_ssl_connect_realcb(F, RB_ERROR_SSL, sconn);
		break;
	case 0:

		return;
	default:
		break;


	}
	rb_ssl_connect_realcb(F, RB_OK, sconn);
}
