server_main()
{
	int cmd, tmp;
	char buf[128];

	if (mkfifo(params.fifo_path, params.fifo_mode) < 0)
		die("mkfifo");

	fifo = open(params.fifo_path, O_RDWR);
	if (fifo < 0)
		die("open");

	sem = semget(key, 2, IPC_CREAT | IPC_EXCL | 0640);
	if (sem < 0)
		die("semget");

	sem_op(0, 1);

	while (1) {
		sem_op(-1, 0);

		read(fifo, buf, 128);

		if (!strcmp(buf, "exit"))
			break;

		tmp = atoi(buf);
		snprintf(buf, 128, "%d", tmp * tmp * tmp);

		write(fifo, buf, strlen(buf) + 1);

		sem_op(1, 1);
	}

	clean_up();

	return 0;
}
