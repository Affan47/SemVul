domlst(const char * const file)
{
    char line[MAXPATHLEN + 256U] = MLST_BEGIN;

    if (modernformat(file, line + (sizeof MLST_BEGIN - 1U),
                     sizeof line - (sizeof MLST_BEGIN - 1U), " ") >= 0) {
        addreply_noformat(0, line);
        addreply_noformat(250, "End.");
    } else {
        addreply_noformat(550, MSG_STAT_FAILURE2);
    }
}
