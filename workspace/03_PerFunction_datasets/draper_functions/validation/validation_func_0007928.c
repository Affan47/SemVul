lrmd_client_destroy(lrmd_client_t* client)
{
	CHECK_ALLOCATED(client, "client", );

	--lrm_objectstats.clientcount;


	unregister_client(client);
	if (client->app_name) {
		free(client->app_name);
		client->app_name = NULL;
	}
	free(client);
}
