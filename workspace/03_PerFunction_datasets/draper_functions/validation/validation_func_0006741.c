InitScriptLibrary()
{

    outstring_log("  ___         _      _   ___          ___ ");
    outstring_log(" / __| __ _ _(_)_ __| |_|   \\ _____ _|_  )");
    outstring_log(" \\__ \\/ _| '_| | '_ \\  _| |) / -_) V // / ");
    outstring_log(" |___/\\__|_| |_| .__/\\__|___/\\___|\\_//___|");
    outstring_log("               |_|                        ");
    outstring_log("                    http://scriptdev2.com/\n");


    bool configFailure = false;
    if (!SD2Config.SetSource(_MANGOSD_CONFIG))
    {
        configFailure = true;
    }
    else
    {
        outstring_log("SD2: Using configuration file %s", _MANGOSD_CONFIG);
    }


    std::string sd2LogFile = SD2Config.GetStringDefault("SD2ErrorLogFile", "scriptdev2-errors.log");
    setScriptLibraryErrorFile(sd2LogFile.c_str(), "SD2");

    if (configFailure)
    {
        script_error_log("Unable to open configuration file. Database will be unaccessible. Configuration values will use default.");
    }


    if (SD2Config.GetIntDefault("ConfVersion", 0) != _MANGOSDCONFVERSION)
    {
        script_error_log("Configuration file version doesn't match expected version. Some config variables may be wrong or missing.");
    }

    outstring_log("\n");


    LoadDatabase();

    outstring_log("SD2: Loading C++ scripts");
    BarGoLink bar(1);
    bar.step();


    m_scripts.resize(GetScriptIdsCount(), NULL);

    FillSpellSummary();

    AddScripts();


    for (uint32 i = 1; i < GetScriptIdsCount(); ++i)
    {
        if (!m_scripts[i])
        {
            script_error_log("No script found for ScriptName '%s'.", GetScriptName(i));
        }
    }

    outstring_log(">> Loaded %i C++ Scripts.", num_sc_scripts);
}
