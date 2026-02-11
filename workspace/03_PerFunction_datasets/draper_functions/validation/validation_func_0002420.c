ZotAttach(PATMT *p)
{
    if(!p)
      return;

    if(p->description)
      free((char *)p->description);

    if(p->filename){
	if(p->flags & A_TMP)
	  our_unlink(p->filename);

	free((char *)p->filename);
    }

    if(p->size)
      free((char *)p->size);

    if(p->id)
      free((char *)p->id);

    p->next = NULL;
}
