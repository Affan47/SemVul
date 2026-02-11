makeAbsolute(const Path& base)
{
	if (!_absolute)
	{
		Path tmp = base;
		tmp.makeDirectory();
		for (StringVec::const_iterator it = _dirs.begin(); it != _dirs.end(); ++it)
		{
			tmp.pushDirectory(*it);
		}
		_node     = tmp._node;
		_device   = tmp._device;
		_dirs     = tmp._dirs;
		_absolute = base._absolute;
	}
	return *this;
}
