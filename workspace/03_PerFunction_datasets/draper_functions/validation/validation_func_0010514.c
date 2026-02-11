msg2html_add_smiley(struct msg2html_info *i,
			 const char *txt, const char *imgurl)
{
	char buf[2];
	struct msg2html_smiley_list *l;

	buf[0]=*txt;
	buf[1]=0;

	if (strlen(i->smiley_index) < sizeof(i->smiley_index)-1)
		strcat(i->smiley_index, buf);


	if ((l=malloc(sizeof(struct msg2html_smiley_list))) != NULL)
	{
		if ((l->code=strdup(txt)) != NULL)
		{
			if ((l->url=strdup(imgurl)) != NULL)
			{
				l->next=i->smileys;
				i->smileys=l;
				return;
			}
			free(l->code);
		}
		free(l);
	}
}
