group(const Direntry &d)
{
	if (d.name == ".")
		return 0;

	if (d.name == "..")
		return 1;

	if (d.isDir)
		return 2;
	return 3;
}
