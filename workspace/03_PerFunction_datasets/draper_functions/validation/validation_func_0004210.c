loadRunner(const KService::Ptr service)
{
    KPluginInfo description(service);
    const QString runnerName = description.pluginName();
    if (!runnerName.isEmpty() && !d->runners.contains(runnerName)) {
        AbstractRunner *runner = d->loadInstalledRunner(service);
        if (runner) {
            d->runners.insert(runnerName, runner);
        }
    }
}
