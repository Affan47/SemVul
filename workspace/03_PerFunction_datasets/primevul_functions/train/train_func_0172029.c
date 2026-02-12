KCleanup::execute( KFileInfo *item )
{
    if ( worksFor( item ) )
    {
	if ( _askForConfirmation && ! confirmation( item ) )
	    return;

	KDirTree  * tree = item->tree();

	executeRecursive( item );

	switch ( _refreshPolicy )
	{
	    case noRefresh:

		break;


	    case refreshThis:
		tree->refresh( item );
		break;


	    case refreshParent:
		tree->refresh( item->parent() );
		break;


	    case assumeDeleted:


		tree->deleteSubtree( item );


		break;
	}
    }

    emit executed();
}
