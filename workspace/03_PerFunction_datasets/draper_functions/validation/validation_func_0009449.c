DeleteAllBreakpoints()
{
    bool debuggerIsRunning = !IsStopped();
    if (debuggerIsRunning)
        DoBreak(true);
    m_State.RemoveAllBreakpoints();

    if (debuggerIsRunning)
        Continue();
}
