GetSpaceGroup (char const *name)
{
	if (!_SpaceGroups.Inited ())
		_SpaceGroups.Init ();
	if (!name)
		return NULL;
	return (_SpaceGroups.sgbn.find (name)!= _SpaceGroups.sgbn.end ())? _SpaceGroups.sgbn[name]: NULL;
}
