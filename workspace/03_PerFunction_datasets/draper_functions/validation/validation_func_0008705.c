smtp_check_thread(thread_t *thread)
{
	checker_t *checker = THREAD_ARG(thread);
	smtp_checker_t *smtp_checker = CHECKER_ARG(checker);
	smtp_host_t *smtp_host = smtp_checker->host_ptr;
	int status;

	status = tcp_socket_state(thread->u.fd, thread, smtp_check_thread);
	switch (status) {
		case connect_error:
			smtp_final(thread, 1, "Error connecting to server %s"
					     , FMT_SMTP_RS(smtp_host));
			return 0;
			break;

		case connect_timeout:
			smtp_final(thread, 1, "Connection timeout to server %s"
					     , FMT_SMTP_RS(smtp_host));
			return 0;
			break;

		case connect_success:
			DBG("SMTP_CHECK Remote SMTP server %s connected"
			    , FMT_SMTP_RS(smtp_host));


			smtp_checker->state = SMTP_START;
			smtp_engine_thread(thread);
			return 0;
			break;
	}


	smtp_final(thread, 1, "Unknown connection error to server %s"
			     , FMT_SMTP_RS(smtp_host));
	return 0;
}
