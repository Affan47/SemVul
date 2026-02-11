RegisterPlugin(FUPlugin* plugin)
{
	if (plugin != NULL)
	{
		if (plugin->HasType(FCPArchive::GetClassType()))
		{
			archivePlugins.push_back((FCPArchive*) plugin);
			return true;
		}
		else if (plugin->HasType(FCPExtraTechnique::GetClassType()))
		{
			FCPExtraTechnique* extraPlugin = (FCPExtraTechnique*) plugin;
			const char* profileName = extraPlugin->GetProfileName();
			if (profileName != NULL && *profileName != 0)
			{
				extraTechniquePlugins.push_back(extraPlugin);
				return true;
			}
		}
	}
	return false;
}
