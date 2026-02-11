print_cycles( u_64 ratio )
	{
	struct pid_cycles_item	*ptr;
	double					t, r, jtot, ptot;
	u_64					total;
	char					category;
	const char				*name;

	r = (double)ratio;
	total = 0ULL;
	jtot = 0.0;
	ptot = 0.0;
	printf("\n\n%48s\n\n","PROCESSES CYCLES");
	my_print_line('*');
	printf("\n");
	printf("%c"COMMSTR" %6s "CYCSTR" %15s %11s\n", ' ', COMMNAME, "pid", "cycles", "jiffies", "percent");
	printf("%c"COMMSTR" %6s "CYCSTR" %15s %11s\n", ' ', COMMUNDERLINE, "---", "------", "-------", "-------");
	for( ptr = pid_cycles_list;  ptr != NULL;  ptr = ptr->next )
		{
		t = ((double)ptr->total_cycles);
		total += ptr->total_cycles;
		jtot += t/r;
		}
	for( ptr = pid_cycles_list;  ptr != NULL;  ptr = ptr->next )
		{
		t = ((double)ptr->total_cycles);
		find_category(ptr->pid,&category,&name);
		printf("%c"COMMSTR" %6"PRId64" "CYCNUM" %15.2f %10.2f%%\n",
					category,
					ptr->name,
					ptr->pid, ptr->total_cycles, t/r, t*100.0/((double)total));
		ptot += t*100.0/((double)total);
		}
	printf("%c"COMMSTR" %6s "CYCNUM" %15.2f %10.2f%%\n", ' ', "", "TOTAL", total, jtot, ptot);
	}
