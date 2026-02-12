KCleanup::executeRecursive( KFileInfo *item )
{
    if ( worksFor( item ) )
    {
	if ( _recurse )
	{


	    KFileInfo * subdir = item->firstChild();

	    while ( subdir )
	    {
		if ( subdir->isDir() )
		{


		    executeRecursive( subdir );
		}
		subdir = subdir->next();
	    }
	}


	runCommand( item, _command );
    }
}
