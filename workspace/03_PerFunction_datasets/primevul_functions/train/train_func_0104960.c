static int netns_exec(int argc, char **argv)
{


	const char *cmd;

	if (argc < 1 && !do_all) {
		fprintf(stderr, "No netns name specified\n");
		return -1;
	}
	if ((argc < 2 && !do_all) || (argc < 1 && do_all)) {
		fprintf(stderr, "No command specified\n");
		return -1;
	}

	if (do_all)
		return do_each_netns(on_netns_exec, --argv, 1);

	if (netns_switch(argv[0]))
		return -1;


	vrf_reset();


	cmd = argv[1];
	return -cmd_exec(cmd, argv + 1, !!batch_mode);
}
