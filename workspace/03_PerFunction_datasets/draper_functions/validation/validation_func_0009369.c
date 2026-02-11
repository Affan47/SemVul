cosm_scif_client(void *unused)
{
	struct cosm_msg msg = { .id = COSM_MSG_HEARTBEAT };
	struct scif_pollepd pollepd;
	int rc;

	allow_signal(SIGKILL);

	while (!kthread_should_stop()) {
		pollepd.epd = client_epd;
		pollepd.events = POLLIN;

		rc = scif_poll(&pollepd, 1, COSM_HEARTBEAT_SEND_MSEC);
		if (rc < 0) {
			if (-EINTR != rc)
				dev_err(&client_spdev->dev,
					"%s %d scif_poll rc %d\n",
					__func__, __LINE__, rc);
			continue;
		}

		if (pollepd.revents & POLLIN)
			cosm_client_recv();

		msg.id = COSM_MSG_HEARTBEAT;
		rc = scif_send(client_epd, &msg, sizeof(msg), SCIF_SEND_BLOCK);
		if (rc < 0)
			dev_err(&client_spdev->dev, "%s %d scif_send rc %d\n",
				__func__, __LINE__, rc);
	}

	dev_dbg(&client_spdev->dev, "%s %d Client thread stopped\n",
		__func__, __LINE__);
	return 0;
}
