irqsoff_print_header(struct seq_file *s)
{
	struct trace_array *tr = irqsoff_trace;

	if (is_graph(tr))
		print_graph_headers_flags(s, GRAPH_TRACER_FLAGS);
	else
		trace_default_header(s);
}
