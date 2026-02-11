printStats(const RunSummary& sol, const SolveStats** stats, std::size_t num) {
	const ProblemStats& pr = sol.ctx.stats();
	const SolveStats* st   = stats[0];
	printSolveStats(*st);
	printf("\n");
	if (lpStats()) {
		printLpStats(*lpStats());
		printf("\n");
	}
	printProblemStats(pr);
	printLemmaStats(*st);
	printJumpStats(*st);
	printThreadStats(stats, num, sol);
	fflush(stdout);
}
