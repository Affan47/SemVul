static void init_busid_table(void)
{
	int i;


	memset(busid_table, 0, sizeof(busid_table));

	spin_lock_init(&busid_table_lock);

	for (i = 0; i < MAX_BUSID; i++)
		spin_lock_init(&busid_table[i].busid_lock);
}
