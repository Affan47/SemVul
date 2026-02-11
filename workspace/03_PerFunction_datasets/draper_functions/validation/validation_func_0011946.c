sender_writecb(struct bufferevent *bev, void *ctx)
{
	if (evbuffer_get_length(bufferevent_get_output(bev)) == 0) {
		bufferevent_disable(bev,EV_READ|EV_WRITE);
		bufferevent_free(bev);
	}
}
