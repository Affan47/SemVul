Initialize()
{

    m_logsDir = sConfig.GetStringDefault("LogsDir", "");
    if (!m_logsDir.empty())
    {
        if ((m_logsDir.at(m_logsDir.length() - 1) != '/') && (m_logsDir.at(m_logsDir.length() - 1) != '\\'))
            { m_logsDir.append("/"); }
    }

    m_logsTimestamp = "_" + GetTimestampStr();


    logfile = openLogFile("LogFile", "LogTimestamp", "w");

    m_gmlog_per_account = sConfig.GetBoolDefault("GmLogPerAccount", false);
    if (!m_gmlog_per_account)
        { gmLogfile = openLogFile("GMLogFile", "GmLogTimestamp", "a"); }
    else
    {

        m_gmlog_filename_format = sConfig.GetStringDefault("GMLogFile", "");
        if (!m_gmlog_filename_format.empty())
        {
            bool m_gmlog_timestamp = sConfig.GetBoolDefault("GmLogTimestamp", false);

            size_t dot_pos = m_gmlog_filename_format.find_last_of(".");
            if (dot_pos != m_gmlog_filename_format.npos)
            {
                if (m_gmlog_timestamp)
                    { m_gmlog_filename_format.insert(dot_pos, m_logsTimestamp); }

                m_gmlog_filename_format.insert(dot_pos, "_#%u");
            }
            else
            {
                m_gmlog_filename_format += "_#%u";

                if (m_gmlog_timestamp)
                    { m_gmlog_filename_format += m_logsTimestamp; }
            }

            m_gmlog_filename_format = m_logsDir + m_gmlog_filename_format;
        }
    }

    charLogfile = openLogFile("CharLogFile", "CharLogTimestamp", "a");
    dberLogfile = openLogFile("DBErrorLogFile", NULL, "a");
    elunaErrLogfile = openLogFile("ElunaErrorLogFile", NULL, "a");
    eventAiErLogfile = openLogFile("EventAIErrorLogFile", NULL, "a");
    raLogfile = openLogFile("RaLogFile", NULL, "a");
    worldLogfile = openLogFile("WorldLogFile", "WorldLogTimestamp", "a");


    m_includeTime  = sConfig.GetBoolDefault("LogTime", false);
    m_logLevel     = LogLevel(sConfig.GetIntDefault("LogLevel", 0));
    m_logFileLevel = LogLevel(sConfig.GetIntDefault("LogFileLevel", 0));
    InitColors(sConfig.GetStringDefault("LogColors", ""));

    m_logFilter = 0;
    for (int i = 0; i < LOG_FILTER_COUNT; ++i)
        if (*logFilterData[i].name)
            if (sConfig.GetBoolDefault(logFilterData[i].configName, logFilterData[i].defaultState))
                { m_logFilter |= (1 << i); }


    m_charLog_Dump = sConfig.GetBoolDefault("CharLogDump", false);
}
