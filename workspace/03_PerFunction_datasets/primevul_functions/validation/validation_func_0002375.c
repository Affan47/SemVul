void CLua::save_persist()
{
    string persist;


    execfile("dlua/persist.lua", true, true);
    callfn("c_save_persist", ">s", &persist);
    if (Options.no_save)
        return;

    FILE *f;
    const string persistfile = _get_persist_file();


    if (persist.empty() && !file_exists(persistfile))
        return;

    f = fopen_u(persistfile.c_str(), "w");
    if (!f)
    {
        mprf(MSGCH_ERROR, "Couldn't open %s for writing!", persistfile.c_str());
        return;
    }

    fprintf(f, "-- %s %s persistent clua file\n"
               "-- WARNING: This file is entirely auto-generated.\n"
            "\n",
            OUTS(CRAWL),
            OUTS(Version::Long));
    fprintf(f, "%s", persist.c_str());
    fclose(f);
}
