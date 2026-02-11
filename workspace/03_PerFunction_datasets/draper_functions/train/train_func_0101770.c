removeVariableUpdates()
{
    QMutableListIterator<GDBCommand*> it = m_commandList;

    while (it.hasNext()) {
        CommandType type = it.next()->type();
        if ((type >= VarEvaluateExpression && type <= VarListChildren) || type == VarUpdate)
            it.remove();
    }
}
