rb_connect_tryconnect(rb_fde_t *F, void *notused)
{
	int retval;

	if(F == NULL || F->connect == NULL || F->connect->callback == NULL)
		return;

	retval = connect(F->fd,
			 (struct sockaddr *)&F->connect->hostaddr,
			 GET_SS_LEN(&F->connect->hostaddr));

	if(retval < 0)
	{


		rb_get_errno();
		if(errno == EISCONN)
			rb_connect_callback(F, RB_OK);
		else if(rb_ignore_errno(errno))

			rb_setselect(F, RB_SELECT_CONNECT, rb_connect_tryconnect, NULL);
		else

			rb_connect_callback(F, RB_ERR_CONNECT);
		return;
	}

	rb_connect_callback(F, RB_OK);
}
