Fclose( FILE *f, int safe )
{
	if ((safe && (fflush( f ) || (UseFSync && fdatasync( fileno( f ) )))) || fclose( f ) == EOF) {
		sys_error( "Error: cannot close file. Disk full?" );
		exit( 1 );
	}
}
