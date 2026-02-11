__dev_pm_qos_flags(struct device *dev, s32 mask)
{
	struct dev_pm_qos *qos = dev->power.qos;
	struct pm_qos_flags *pqf;
	s32 val;

	lockdep_assert_held(&dev->power.lock);

	if (IS_ERR_OR_NULL(qos))
		return PM_QOS_FLAGS_UNDEFINED;

	pqf = &qos->flags;
	if (list_empty(&pqf->list))
		return PM_QOS_FLAGS_UNDEFINED;

	val = pqf->effective_flags & mask;
	if (val)
		return (val == mask) ? PM_QOS_FLAGS_ALL : PM_QOS_FLAGS_SOME;

	return PM_QOS_FLAGS_NONE;
}
