modeMint2Host(uint16 m)
{
	mode_t result = 0;


	if ( m & 00001 ) result |= S_IXOTH;
	if ( m & 00002 ) result |= S_IWOTH;
	if ( m & 00004 ) result |= S_IROTH;
	if ( m & 00010 ) result |= S_IXGRP;
	if ( m & 00020 ) result |= S_IWGRP;
	if ( m & 00040 ) result |= S_IRGRP;
	if ( m & 00100 ) result |= S_IXUSR;
	if ( m & 00200 ) result |= S_IWUSR;
	if ( m & 00400 ) result |= S_IRUSR;
	if ( m & 01000 ) result |= S_ISVTX;
	if ( m & 02000 ) result |= S_ISGID;
	if ( m & 03000 ) result |= S_ISUID;

	if ( m & 0010000 ) result |= S_IFSOCK;
	if ( m & 0020000 ) result |= S_IFCHR;
	if ( m & 0040000 ) result |= S_IFDIR;
	if ( m & 0060000 ) result |= S_IFBLK;
	if ( m & 0100000 ) result |= S_IFREG;
	if ( m & 0120000 ) result |= S_IFIFO;

	if ( m & 0160000 ) result |= S_IFLNK;

	D2(bug("					(statmode: %#04o)", result));

	return result;
}
