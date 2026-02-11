Initialize()
	{
		if (pluginManager == NULL)
		{
			pluginManager = new FColladaPluginManager();
			pluginManager->RegisterPlugin(CreatePlugin(0));
		}
		++libraryInitializationCount;
	}
