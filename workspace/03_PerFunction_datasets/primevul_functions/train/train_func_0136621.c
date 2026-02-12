perf_cgroup_set_timestamp(struct task_struct *task,
			  struct perf_event_context *ctx)
{
	struct perf_cgroup *cgrp;
	struct perf_cgroup_info *info;
	struct cgroup_subsys_state *css;


	if (!task || !ctx->nr_cgroups)
		return;

	cgrp = perf_cgroup_from_task(task, ctx);

	for (css = &cgrp->css; css; css = css->parent) {
		cgrp = container_of(css, struct perf_cgroup, css);
		info = this_cpu_ptr(cgrp->info);
		info->timestamp = ctx->timestamp;
	}
}
