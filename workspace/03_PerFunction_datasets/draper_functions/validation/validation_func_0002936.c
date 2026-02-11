http_read_thread(thread_t * thread)
{
	checker_t *checker = THREAD_ARG(thread);
	http_checker_t *http_get_check = CHECKER_ARG(checker);
	http_t *http = HTTP_ARG(http_get_check);
	request_t *req = HTTP_REQ(http);
	unsigned timeout = checker->co->connection_to;
	unsigned char digest[16];
	int r = 0;
	int val;


	if (thread->type == THREAD_READ_TIMEOUT)
		return timeout_epilog(thread, "=> HTTP CHECK failed on service"
				      " : recevice data <=\n\n", "HTTP read");


	val = fcntl(thread->u.fd, F_GETFL, 0);
	fcntl(thread->u.fd, F_SETFL, val | O_NONBLOCK);


	r = read(thread->u.fd, req->buffer + req->len,
		 MAX_BUFFER_LENGTH - req->len);


	fcntl(thread->u.fd, F_SETFL, val);


	if (r == -1 && (errno == EAGAIN || errno == EINTR)) {
		log_message(LOG_INFO, "Read error with server %s: %s"
				    , FMT_HTTP_RS(checker)
				    , strerror(errno));
		thread_add_read(thread->master, http_read_thread, checker,
				thread->u.fd, timeout);
		return 0;
	}

	if (r == -1 || r == 0) {


		MD5_Final(digest, &req->context);

		if (r == -1) {

			if (svr_checker_up(checker->id, checker->rs)) {
				log_message(LOG_INFO, "Read error with server %s: %s"
				       , FMT_HTTP_RS(checker)
				       , strerror(errno));
				smtp_alert(checker->rs, NULL, NULL,
					   "DOWN",
					   "=> HTTP CHECK failed on service"
					   " : cannot receive data <=");
				update_svr_checker_state(DOWN, checker->id
							     , checker->vs
							     , checker->rs);
			}
			return epilog(thread, 1, 0, 0);
		}


		http_handle_response(thread, digest, (!req->extracted) ? 1 : 0);

	} else {


		http_process_response(req, r);


		thread_add_read(thread->master, http_read_thread, checker,
				thread->u.fd, timeout);
	}

	return 0;
}
