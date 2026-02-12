EXPORTED void annotate_done(void)
{

    if (annotatemore_dbopen) {
        annotatemore_close();
    }
    annotate_initialized = 0;
}
