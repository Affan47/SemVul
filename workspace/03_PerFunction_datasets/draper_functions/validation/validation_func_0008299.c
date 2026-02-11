cut_run_context_get_status (CutRunContext *context)
{
    CutRunContextPrivate *priv;
    CutTestResultStatus status;

    priv = CUT_RUN_CONTEXT_GET_PRIVATE(context);

    if (priv->crashed) {
        status = CUT_TEST_RESULT_CRASH;
    } else if (priv->n_errors > 0) {
        status = CUT_TEST_RESULT_ERROR;
    } else if (priv->n_failures > 0) {
        status = CUT_TEST_RESULT_FAILURE;
    } else if (priv->n_pendings > 0) {
        status = CUT_TEST_RESULT_PENDING;
    } else if (priv->n_omissions > 0) {
        status = CUT_TEST_RESULT_OMISSION;
    } else if (priv->n_notifications > 0) {
        status = CUT_TEST_RESULT_NOTIFICATION;
    } else {
        status = CUT_TEST_RESULT_SUCCESS;
    }

    return status;
}
