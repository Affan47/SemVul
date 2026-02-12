static void __execlists_kick(struct intel_engine_execlists *execlists)
{

	tasklet_hi_schedule(&execlists->tasklet);
}
