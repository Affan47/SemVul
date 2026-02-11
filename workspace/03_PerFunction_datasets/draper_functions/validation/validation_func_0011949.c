cmsUnregisterPlugins(void)
{
    _cmsRegisterMemHandlerPlugin(NULL);
    _cmsRegisterInterpPlugin(NULL);
    _cmsRegisterTagTypePlugin(NULL);
    _cmsRegisterTagPlugin(NULL);
    _cmsRegisterFormattersPlugin(NULL);
    _cmsRegisterRenderingIntentPlugin(NULL);
    _cmsRegisterParametricCurvesPlugin(NULL);
    _cmsRegisterMultiProcessElementPlugin(NULL);
    _cmsRegisterOptimizationPlugin(NULL);

    if (PluginPool != NULL)
        _cmsSubAllocDestroy(PluginPool);

    PluginPool = NULL;
}
