SplitPathFile( CString s, CString & path, CString & file )
{
	int i;

	path.Empty();
	file.Empty();

	if ( (i = s.FindRev('\\')) == -1 )
		i = s.FindRev('/');

	if ( i == -1 )
	{
		file = s;
	}
	else
	{
		path = s.Left(i+1);
		file = s.Mid(i+1,s.Length()-i-1);
	}
}
