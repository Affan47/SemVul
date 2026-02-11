reset() {
	CoreStats::reset();
	if (queue)   queue->reset();
	if (jumps)   jumps->reset();
	if (parallel)parallel->reset();
}
