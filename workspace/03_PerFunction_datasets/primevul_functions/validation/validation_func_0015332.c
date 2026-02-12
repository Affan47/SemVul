process_remove_all_identities(SocketEntry *e)
{
	Identity *id;

	debug2_f("entering");

	for (id = TAILQ_FIRST(&idtab->idlist); id;
	    id = TAILQ_FIRST(&idtab->idlist)) {
		TAILQ_REMOVE(&idtab->idlist, id, next);
		free_identity(id);
	}


	idtab->nentries = 0;


	send_status(e, 1);
}
