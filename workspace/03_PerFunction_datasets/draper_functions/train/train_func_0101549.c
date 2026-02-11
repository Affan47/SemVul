cb_complete_run (CutRunContext *run_context, gboolean success,
                 CutConsoleUI *console)
{
    CutVerboseLevel verbose_level;

    notify(console, run_context, success);

    verbose_level = console->verbose_level;
    if (verbose_level < CUT_VERBOSE_LEVEL_NORMAL)
        return;

    if (verbose_level == CUT_VERBOSE_LEVEL_NORMAL)
        g_print("\n");

    print_results(console, run_context);

    g_print("\n");
    g_print("Finished in %f seconds (total: %f seconds)",
            cut_run_context_get_elapsed(run_context),
            cut_run_context_get_total_elapsed(run_context));
    g_print("\n\n");

    print_summary(console, run_context);
}
