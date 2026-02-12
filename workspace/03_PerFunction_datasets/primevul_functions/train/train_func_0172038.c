KCleanup::readConfig()
{
    KConfigGroup config = KGlobal::config()->group(_id);

    bool valid = config.readEntry( "valid", false	);


    if ( valid )
    {
	_command		= config.readEntry ( "command"		);
	_enabled		= config.readEntry ( "enabled"		, false );
	_worksForDir		= config.readEntry ( "worksForDir"	, true  );
	_worksForFile		= config.readEntry ( "worksForFile"	, true  );
	_worksForDotEntry	= config.readEntry ( "worksForDotEntry"	, true  );
	_worksLocalOnly		= config.readEntry ( "worksLocalOnly"	, true  );
	_recurse		= config.readEntry ( "recurse"		, false	);
	_askForConfirmation	= config.readEntry ( "askForConfirmation"	, false	);
	_refreshPolicy		= (KCleanup::RefreshPolicy) config.readEntry( "refreshPolicy", 0);
	setTitle( config.readEntry( "title" ) );
    }
}
