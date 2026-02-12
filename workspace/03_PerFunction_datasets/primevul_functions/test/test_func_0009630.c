static void free_clt(struct rtrs_clt_sess *clt)
{
	free_permits(clt);
	free_percpu(clt->pcpu_path);


	device_unregister(&clt->dev);
}
