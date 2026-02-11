dev_pm_qos_constraints_allocate(struct device *dev)
{
	struct dev_pm_qos *qos;
	struct pm_qos_constraints *c;
	struct blocking_notifier_head *n;

	qos = kzalloc(sizeof(*qos), GFP_KERNEL);
	if (!qos)
		return -ENOMEM;

	n = kzalloc(sizeof(*n), GFP_KERNEL);
	if (!n) {
		kfree(qos);
		return -ENOMEM;
	}
	BLOCKING_INIT_NOTIFIER_HEAD(n);

	c = &qos->resume_latency;
	plist_head_init(&c->list);
	c->target_value = PM_QOS_RESUME_LATENCY_DEFAULT_VALUE;
	c->default_value = PM_QOS_RESUME_LATENCY_DEFAULT_VALUE;
	c->no_constraint_value = PM_QOS_RESUME_LATENCY_DEFAULT_VALUE;
	c->type = PM_QOS_MIN;
	c->notifiers = n;

	c = &qos->latency_tolerance;
	plist_head_init(&c->list);
	c->target_value = PM_QOS_LATENCY_TOLERANCE_DEFAULT_VALUE;
	c->default_value = PM_QOS_LATENCY_TOLERANCE_DEFAULT_VALUE;
	c->no_constraint_value = PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT;
	c->type = PM_QOS_MIN;

	INIT_LIST_HEAD(&qos->flags.list);

	spin_lock_irq(&dev->power.lock);
	dev->power.qos = qos;
	spin_unlock_irq(&dev->power.lock);

	return 0;
}
