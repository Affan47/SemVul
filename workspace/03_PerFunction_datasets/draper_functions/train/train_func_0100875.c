PerformTests(void)
{
    int                     Loop;

    for (Loop = 0; Loop < Index; Loop++)
        if (Test[Loop].SkipFlag) {
            MESSAGE(2, ("Skipping -- %s (%s) \n", Test[Loop].Description, Test[Loop].Name));
        } else {
            MESSAGE(2, ("Testing  -- %s (%s) \n", Test[Loop].Description, Test[Loop].Name));
            MESSAGE(5, ("===============================================\n"));
            Test[Loop].NumErrors = num_errs;
	    Test_parameters = Test[Loop].Parameters;
	    ALARM_ON;
            Test[Loop].Call();
	    ALARM_OFF;
            Test[Loop].NumErrors = num_errs - Test[Loop].NumErrors;
            MESSAGE(5, ("===============================================\n"));
            MESSAGE(5, ("There were %d errors detected.\n\n", (int)Test[Loop].NumErrors));
        }

    Test_parameters = NULL;
    MESSAGE(2, ("\n\n"))

    if (num_errs)
        print_func("!!! %d Error(s) were detected !!!\n\n", (int) num_errs);
    else
        print_func("All tests were successful. \n\n");
}
