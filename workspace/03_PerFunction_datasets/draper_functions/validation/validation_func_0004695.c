buildin_killmonster_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md = NULL;
	char *event=va_arg(ap,char *);
	int allflag=va_arg(ap,int);

	nullpo_retr(0, bl);
	nullpo_retr(0, md = (struct mob_data *)bl);

	if(!allflag) {
		if(strcmp(event,md->npc_event) == 0)
			unit_remove_map(bl,1,0);
	} else {
		if(md->spawndelay1 == -1 && md->spawndelay2 == -1)
			unit_remove_map(bl,1,0);
	}
	return 0;
}
