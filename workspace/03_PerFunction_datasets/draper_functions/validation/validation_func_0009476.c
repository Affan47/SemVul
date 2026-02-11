JCfreeServerList(char **list)
{
	int count = 0;
	while (list[count]) {
		free(list[count++]);
	}
	free(list);
}
