LogTimeString(void)
{
    std::time_t rawTime;

    std::time(&rawTime);
    std::tm *pTM = std::gmtime(&rawTime);

    std::ostringstream timeStream;
    timeStream << setfill('0') << setw(4) << 1900+pTM->tm_year;
    timeStream << setw(2) << pTM->tm_mon;
    timeStream << setw(2) << pTM->tm_mday;
    timeStream << "T" << setw(2) << pTM->tm_hour;
    timeStream << setw(2) << pTM->tm_min;
    timeStream << setw(2) << pTM->tm_sec;
    timeStream << "Z";
    return timeStream.str();
}
