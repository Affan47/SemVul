afInitLoopIDs (AFfilesetup setup, int instid, const int *loopids, int nloops)
{
	if (!_af_filesetup_ok(setup))
		return;

	if (!_af_unique_ids(loopids, nloops, "loop", AF_BAD_LOOPID))
		return;

	InstrumentSetup *instrument = setup->getInstrument(instid);
	if (!instrument)
		return;

	instrument->freeLoops();
	if (!instrument->allocateLoops(nloops))
		return;

	for (int i=0; i < nloops; i++)
		instrument->loops[i].id = loopids[i];
}
