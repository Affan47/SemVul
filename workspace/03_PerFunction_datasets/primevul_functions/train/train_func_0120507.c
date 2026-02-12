cmsBool  _cmsRegisterOptimizationPlugin(cmsContext ContextID, cmsPluginBase* Data)
{
    cmsPluginOptimization* Plugin = (cmsPluginOptimization*) Data;
    _cmsOptimizationPluginChunkType* ctx = ( _cmsOptimizationPluginChunkType*) _cmsContextGetClientChunk(ContextID, OptimizationPlugin);
    _cmsOptimizationCollection* fl;

    if (Data == NULL) {

        ctx->OptimizationCollection = NULL;
        return TRUE;
    }


    if (Plugin ->OptimizePtr == NULL) return FALSE;

    fl = (_cmsOptimizationCollection*) _cmsPluginMalloc(ContextID, sizeof(_cmsOptimizationCollection));
    if (fl == NULL) return FALSE;


    fl ->OptimizePtr = Plugin ->OptimizePtr;


    fl ->Next = ctx->OptimizationCollection;


    ctx ->OptimizationCollection = fl;


    return TRUE;
}
