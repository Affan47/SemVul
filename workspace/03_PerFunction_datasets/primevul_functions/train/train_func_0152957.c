cmsBool _cmsRegisterParametricCurvesPlugin(cmsContext id, cmsPluginBase* Data)
{
    cmsPluginParametricCurves* Plugin = (cmsPluginParametricCurves*) Data;
    _cmsParametricCurvesCollection* fl;

    if (Data == NULL) {

          ParametricCurves =  &DefaultCurves;
          return TRUE;
    }

    fl = (_cmsParametricCurvesCollection*) _cmsPluginMalloc(id, sizeof(_cmsParametricCurvesCollection));
    if (fl == NULL) return FALSE;


    fl ->Evaluator  = Plugin ->Evaluator;
    fl ->nFunctions = Plugin ->nFunctions;


    if (fl ->nFunctions > MAX_TYPES_IN_LCMS_PLUGIN)
        fl ->nFunctions = MAX_TYPES_IN_LCMS_PLUGIN;


    memmove(fl->FunctionTypes,  Plugin ->FunctionTypes,   fl->nFunctions * sizeof(cmsUInt32Number));
    memmove(fl->ParameterCount, Plugin ->ParameterCount,  fl->nFunctions * sizeof(cmsUInt32Number));


    fl ->Next = ParametricCurves;
    ParametricCurves = fl;


    return TRUE;
}
