KCleanup::selectionChanged( KFileInfo *selection )
{
    bool enabled = false;
    _selection = selection;

    if ( selection )
    {
	enabled = worksFor( selection );

	if ( ! selection->isFinished() )
	{


	    switch ( _refreshPolicy )
	    {

		case refreshThis:
		case refreshParent:
		case assumeDeleted:


		    enabled = false;
		    break;

		default:
		    break;
	    }

	}
    }

    KAction::setEnabled( enabled );
}
