cosm_scif_init(void)
{
	int rc = cosm_scif_listen();

	if (rc) {
		pr_err("%s %d cosm_scif_listen rc %d\n",
		       __func__, __LINE__, rc);
		goto err;
	}

	server_thread = kthread_run(cosm_scif_server, NULL, "cosm_server");
	if (IS_ERR(server_thread)) {
		rc = PTR_ERR(server_thread);
		pr_err("%s %d kthread_run rc %d\n", __func__, __LINE__, rc);
		goto listen_exit;
	}
	return 0;
listen_exit:
	cosm_scif_listen_exit();
err:
	return rc;
}
