KCleanup::runCommand ( const KFileInfo *	item,
		       const QString &		command ) const
{
    K3Process	proc;
    KDirSaver	dir( itemDir( item ) );
    QString	cmd( expandVariables( item, command ));

#if VERBOSE_RUN_COMMAND
    printf( "\ncd " );
    fflush( stdout );
    system( "pwd" );
    QTextCodec * codec = QTextCodec::codecForLocale();
    printf( "%s\n", (const char *) codec->fromUnicode( cmd ) );
    fflush( stdout );
#endif

#if ! SIMULATE_COMMAND
    proc << "sh";
    proc << "-c";
    proc << cmd;

    switch ( _refreshPolicy )
    {
	case noRefresh:
	case assumeDeleted:


	    proc.start( K3Process::DontCare );
	    break;


	case refreshThis:
	case refreshParent:


	    QApplication::setOverrideCursor( Qt::WaitCursor );
	    proc.start( K3Process::Block );
	    QApplication::restoreOverrideCursor();
	    break;
    }

#endif
}
