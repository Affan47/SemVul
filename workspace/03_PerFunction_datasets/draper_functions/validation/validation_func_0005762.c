putModemLine(const char* cp, long ms)
{
    u_int cc = strlen(cp);
    server.traceStatus(FAXTRACE_MODEMCOM, "<-- [%u:%s\\r]", cc+1, cp);
    static const char CR = '\r';
    return (server.putModem1(cp, cc, ms) && server.putModem1(&CR, 1, ms));
}
