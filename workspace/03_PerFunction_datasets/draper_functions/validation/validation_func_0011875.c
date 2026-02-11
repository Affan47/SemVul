addBuiltIn(IrisNetProvider *p)
	{
		PluginInstance *i = PluginInstance::fromInstance(p);
		if(!tryAdd(i, true))
			delete i;
	}
