ClearContent()
{
	if ( !HasChildren() ) {
		return;
	}

	LinkedList *cgp = GET_FIRST(&Children);
	LinkedList *cgp_next;

	while ( cgp && (cgp != END_OF_LIST(&Children)) ) {
		cgp_next = GET_NEXT(cgp);
		delete cgp;
		cgp = cgp_next;
	}
}
