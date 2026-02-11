overconstrained_state_spaces_should_be_detected(void) {
    theft *t = theft_init(0);
    struct theft_trial_report report;

    theft_cfg cfg = {
        .fun = prop_bool_tautology,
        .type_info = { &bool_info },
        .report = &report,
        .trials = 100,
    };

    theft_run_res res = theft_run(t, &cfg);
    theft_free(t);
    ASSERT_EQ(THEFT_RUN_FAIL, res);
    ASSERT_EQ(2, report.fail);
    ASSERT_EQ(98, report.dup);
    PASS();
}
