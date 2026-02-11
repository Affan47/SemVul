verify_remote_names(int nr_heads, char **heads)
{
	int i;

	for (i = 0; i < nr_heads; i++) {
		const char *remote = strchr(heads[i], ':');

		remote = remote ? (remote + 1) : heads[i];
		switch (check_ref_format(remote)) {
		case 0:
		case -2:


		case -3:
			continue;
		}
		die("remote part of refspec is not a valid name in %s",
		    heads[i]);
	}
}
