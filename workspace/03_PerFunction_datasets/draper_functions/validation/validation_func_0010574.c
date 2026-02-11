hook_main(int *argc,char ** argv)
{
	int i;
	char **tmp;

	if(old_hook!=NULL)
	{
		old_hook(argc,argv);
	}

	arg_count=*argc;

	GB.NewArray((void*)(&cmd_arg),sizeof(*cmd_arg),0);

	for(i=0;i<*argc;i++)
	{
		tmp=(char **)GB.Add((void*)(&cmd_arg));
		*tmp = GB.NewZeroString(argv[i]);

	}
	*argc=1;
	return;
}
