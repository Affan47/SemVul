Note_flags2str(char f, char *s)
{
	s[0] = 0;
	if(f & NOTE_NEW)	strcat(s,"n");
	if(f & NOTE_READ)	strcat(s,"r");
	if(f & NOTE_MEMO)	strcat(s,"m");
	if(f & NOTE_WALL)	strcat(s,"w");
	if(f & NOTE_SAVE)	strcat(s,"s");
	if(f & NOTE_NOTICE)	strcat(s,"!");
	if(s[0] == 0)		strcat(s,"-");
}
