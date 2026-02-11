main(int argc, char **argv)
{
	cmd_args_t *args = NULL;
	int rc = 0;


	if ((rc = init()))
		return rc;


	if ((rc = dev_init()))
		goto out;


	if ((args = args_init(argc, argv)) == NULL) {
		rc = -1;
		goto out;
	}


	if (args->args_verbose)
		fprintf(stdout, "%s", splat_version);


	if (args->args_do_list) {
		subsystem_list(subsystems, 0);
		goto out;
	}


	if (args->args_do_all) {
		if ((rc = test_add_all(args)))
			goto out;
	}


	if ((rc = tests_run(args)))
		goto out;

out:
	if (args != NULL)
		args_fini(args);

	dev_fini();
	fini();
	return rc;
}
