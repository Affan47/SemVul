fnic_fc_trace_free(void)
{
	fnic_fc_tracing_enabled = 0;
	fnic_fc_trace_debugfs_terminate();
	if (fc_trace_entries.page_offset) {
		vfree((void *)fc_trace_entries.page_offset);
		fc_trace_entries.page_offset = NULL;
	}
	if (fnic_fc_ctlr_trace_buf_p) {
		vfree((void *)fnic_fc_ctlr_trace_buf_p);
		fnic_fc_ctlr_trace_buf_p = 0;
	}
	pr_info("fnic:Successfully FC_CTLR Freed Trace Buffer\n");
}
