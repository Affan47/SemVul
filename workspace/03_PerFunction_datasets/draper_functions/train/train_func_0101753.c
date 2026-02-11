grow_dirent_delete( struct grow_dirent *d )
{
	struct grow_dirent *n;

	while(d) {
		if(d->name) free(d->name);
		if(d->linkname) free(d->linkname);
		grow_dirent_delete(d->children);
		n = d->next;
		free(d);
		d = n;
	}
}
