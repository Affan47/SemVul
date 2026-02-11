get_module_devices(char *	modname)
{
	char	before_names[10][IFNAMSIZ + 1];
	int	before_num;
	char	after_names[15][IFNAMSIZ + 1];
	int	after_num;
	int	firstone = -1;
	int	pid;
	int	i, j;
	int	ret;


	before_num = get_devlist(before_names, IFNAMSIZ + 1, 10);
	if(before_num < 0) {
		fprintf(stderr, "Could not get device name list.\n");
		exit(-1);
	}


	ret = load_module(modname);
	if(ret) {
		fprintf(stderr, "Invalid module name [%s] !\n", device);
		print_usage();
		exit(-1);
	}


	after_num = get_devlist(after_names, IFNAMSIZ + 1, 15);
	if(after_num <= 0) {
		fprintf(stderr, "Could not get device name list.\n");
		exit(-1);
	}


	for(i = 0; i < after_num; i++) {

		for(j = 0; j < before_num; j++) {
			if(!strcmp(before_names[j], after_names[i]))
				break;
		}

		if(j == before_num) {

			if(firstone >= 0) {
				fprintf(stderr,
					"Found additional interface [%s]\n",
					after_names[i]);


				pid = fork();

				if(!pid) {

					strcpy(device, after_names[i]);

					return(0);
				}


			} else {

				firstone = i;
				strcpy(device, after_names[i]);
				fprintf(stderr, "Found interface [%s]\n",
					device);
			}
		}
	}
	return(0);
}
