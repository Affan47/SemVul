oscar_chatnav_connect(AyConnection *fd, int error, void *data)
{
	eb_local_account *account = (eb_local_account *)data;
	struct eb_aim_local_account_data *alad =
		(struct eb_aim_local_account_data *)account->
		protocol_local_account_data;

	if (!fd) {
		WARNING(("unable to create socket to chatnav server\n"))
			return;
	}

	alad->conn_chatnav->fd = ay_connection_get_fd(fd);

	LOG(("oscar_chatnav_connect(): fd=%d, error=%d", alad->conn_chatnav->fd,
			error))

		ay_connection_free_no_close(fd);

	aim_conn_completeconnect(&(alad->aimsess), alad->conn_chatnav);

	alad->input_chatnav =
		eb_input_add(alad->conn_chatnav->fd,
		EB_INPUT_READ | EB_INPUT_EXCEPTION, ay_aim_callback, account);
}
