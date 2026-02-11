GListChangeLine(GGadget *list,int pos, const unichar_t *line) {
    GTextInfo **old, **new;
    int32 i,len;

    old = GGadgetGetList(list,&len);
    new = gcalloc(len+1,sizeof(GTextInfo *));
    for ( i=0; i<len; ++i ) {
	new[i] = galloc(sizeof(GTextInfo));
	*new[i] = *old[i];
	if ( i!=pos )
	    new[i]->text = u_copy(new[i]->text);
	else
	    new[i]->text = u_copy(line);
    }
    new[i] = gcalloc(1,sizeof(GTextInfo));
    GGadgetSetList(list,new,false);
    GGadgetScrollListToPos(list,pos);
return( new[pos]);
}
