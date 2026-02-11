EditBreakpoint(const wxString& filename, int line)
{
    Items::iterator it = FindBreakpoint(filename, line);
    if (it != m_breakpoints.end())
        BreakpointProperties(*it);
}
