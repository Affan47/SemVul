profiler_getstats(ProfilerObject *pObj, PyObject* noarg)
{
    statscollector_t collect;
    if (pending_exception(pObj))
        return NULL;
    if (!pObj->externalTimer)
        collect.factor = hpTimerUnit();
    else if (pObj->externalTimerUnit > 0.0)
        collect.factor = pObj->externalTimerUnit;
    else
        collect.factor = 1.0 / DOUBLE_TIMER_PRECISION;
    collect.list = PyList_New(0);
    if (collect.list == NULL)
        return NULL;
    if (RotatingTree_Enum(pObj->profilerEntries, statsForEntry, &collect)
        != 0) {
        Py_DECREF(collect.list);
        return NULL;
    }
    return collect.list;
}
