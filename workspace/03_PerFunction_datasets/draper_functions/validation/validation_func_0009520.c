start(string name)
{
	Profile *prof = get(name);
	prof->start();
}
