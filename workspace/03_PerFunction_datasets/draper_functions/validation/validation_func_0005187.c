Next()
{
    wxCompilerCommandsNode* node = m_Commands.GetFirst();
    if (!node)
        return 0;
    CompilerCommand* cmd = node->GetData();
    m_Commands.Erase(node);
    m_LastWasRun = cmd ? cmd->isRun : false;
    return cmd;
}
