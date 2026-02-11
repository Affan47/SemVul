i915_ppgtt_info(struct seq_file *m, void *data)
{
	struct drm_info_node *node = m->private;
	struct drm_device *dev = node->minor->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_file *file;

	int ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		return ret;
	intel_runtime_pm_get(dev_priv);

	if (INTEL_INFO(dev)->gen >= 8)
		gen8_ppgtt_info(m, dev);
	else if (INTEL_INFO(dev)->gen >= 6)
		gen6_ppgtt_info(m, dev);

	list_for_each_entry_reverse(file, &dev->filelist, lhead) {
		struct drm_i915_file_private *file_priv = file->driver_priv;
		struct task_struct *task;

		task = get_pid_task(file->pid, PIDTYPE_PID);
		if (!task) {
			ret = -ESRCH;
			goto out_put;
		}
		seq_printf(m, "\nproc: %s\n", task->comm);
		put_task_struct(task);
		idr_for_each(&file_priv->context_idr, per_file_ctx,
			     (void *)(unsigned long)m);
	}

out_put:
	intel_runtime_pm_put(dev_priv);
	mutex_unlock(&dev->struct_mutex);

	return ret;
}
