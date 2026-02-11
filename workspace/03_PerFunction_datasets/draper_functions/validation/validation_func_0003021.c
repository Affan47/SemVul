runTestRequest(const TestNode* root,
             int argc,
             const char* const argv[])
{


    const TestNode*    toRun;
    int                i;
    int                doList = FALSE;
    int                subtreeOptionSeen = FALSE;

    int                errorCount = 0;

    toRun = root;

    for( i=1; i<argc; i++)
    {
        if ( argv[i][0] == '/' )
        {
            printf("Selecting subtree '%s'\n", argv[i]);

            if ( argv[i][1] == 0 )
                toRun = root;
            else
                toRun = getTest(root, argv[i]);

            if ( toRun == NULL )
            {
                printf("* Could not find any matching subtree\n");
                return -1;
            }

            if( doList == TRUE)
                showTests(toRun);
            else
                runTests(toRun);

            errorCount += ERROR_COUNT;

            subtreeOptionSeen = TRUE;
        } else if ((strcmp( argv[i], "-a") == 0) || (strcmp(argv[i],"-all") == 0)) {
            subtreeOptionSeen=FALSE;
        } else if (strcmp( argv[i], "-l") == 0) {
            doList = TRUE;
        }

    }

    if( subtreeOptionSeen == FALSE)
    {
        if( doList == TRUE)
            showTests(toRun);
        else
            runTests(toRun);

        errorCount += ERROR_COUNT;
    }
    else
    {
        if( ( doList == FALSE ) && ( errorCount > 0 ) )
            printf(" Total errors: %d\n", errorCount );
    }

    REPEAT_TESTS_INIT = 1;

    return errorCount;
}
