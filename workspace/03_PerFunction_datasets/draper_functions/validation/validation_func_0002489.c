processOptions()
{
	defineOptions(_options);
	OptionProcessor processor(_options);
	processor.setUnixStyle(_unixOptions);
	_args.erase(_args.begin());
	ArgVec::iterator it = _args.begin();
	while (it != _args.end() && !_stopOptionsProcessing)
	{
		std::string name;
		std::string value;
		if (processor.process(*it, name, value))
		{
			if (!name.empty())
			{
				handleOption(name, value);
			}
			it = _args.erase(it);
		}
		else ++it;
	}
	if (!_stopOptionsProcessing)
		processor.checkRequired();
}
