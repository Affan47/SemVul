printCPUxWait( const char* cmd )
{
	int id;

	if ( StatDirty )
		processStat();

	sscanf( cmd + 7, "%d", &id );
	output( "%f\n", SMPLoad[ id ].waitLoad );
}
