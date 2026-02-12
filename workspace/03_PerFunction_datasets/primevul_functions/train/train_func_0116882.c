qemuProcessDropUnknownCPUFeatures(const char *name,
                                  virCPUFeaturePolicy policy,
                                  void *opaque)
{
    const char **features = opaque;

    if (policy != VIR_CPU_FEATURE_DISABLE &&
        policy != VIR_CPU_FEATURE_FORBID)
        return true;

    if (g_strv_contains(features, name))
        return true;


    return false;
}
