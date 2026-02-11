extensionsInitialized()
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << "FormManagerPlugin::extensionsInitialized";


    if (!user())
        return;
    if (user()->uuid().isEmpty())
        return;

    messageSplash(tr("Initializing form manager plugin..."));


    episodeBase()->initialize();
    formManager().checkFormUpdates();

    addAutoReleasedObject(new Core::PluginAboutPage(pluginSpec(), this));


    _mode = new FormManagerMode(this);
}
