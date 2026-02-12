static int perf_event_set_filter(struct perf_event *event, void __user *arg)
{
	int ret = -EINVAL;
	char *filter_str;

	filter_str = strndup_user(arg, PAGE_SIZE);
	if (IS_ERR(filter_str))
		return PTR_ERR(filter_str);

#ifdef CONFIG_EVENT_TRACING
	if (perf_event_is_tracing(event)) {
		struct perf_event_context *ctx = event->ctx;


		mutex_unlock(&ctx->mutex);
		ret = ftrace_profile_set_filter(event, event->attr.config, filter_str);
		mutex_lock(&ctx->mutex);
	} else
#endif
	if (has_addr_filter(event))
		ret = perf_event_set_addr_filter(event, filter_str);

	kfree(filter_str);
	return ret;
}
