socket_input_handler_bev(struct bufferevent *bev, void* arg)
{

	if (bev) {

		if(!arg) {
			read_spare_buffer_bev(bev);
			return;
		}

		ioa_socket_handle s = (ioa_socket_handle) arg;

		if(bev != s->bev) {
			TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "!!! %s socket: 0x%lx: wrong bev\n", __FUNCTION__,(long)s);
			read_spare_buffer_bev(bev);
			return;
		}

		if((s->magic != SOCKET_MAGIC)||(s->done)) {
			TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "!!!%s on socket: 0x%lx, st=%d, sat=%d\n", __FUNCTION__, (long) s, s->st, s->sat);
			TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "!!! %s socket: 0x%lx was closed\n", __FUNCTION__,(long)s);
			read_spare_buffer_bev(bev);
			return;
		}

		{
			size_t cycle = 0;
			do {
				if(ioa_socket_tobeclosed(s)) {
					read_spare_buffer_bev(s->bev);
					break;
				}
				if (socket_input_worker(s) <= 0)
					break;
			} while((cycle++<128) && (s->bev));
		}

		if((s->magic != SOCKET_MAGIC)||(s->done)) {
			TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "!!!%s (1) on socket: 0x%lx, st=%d, sat=%d\n", __FUNCTION__, (long) s, s->st, s->sat);
			TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "!!! %s socket: 0x%lx was closed\n", __FUNCTION__,(long)s);
			return;
		}

		close_ioa_socket_after_processing_if_necessary(s);
	}
}
