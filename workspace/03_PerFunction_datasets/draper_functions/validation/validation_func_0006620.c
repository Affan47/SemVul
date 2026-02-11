doReapply()
{
    if (m_cmds.count() == 0) {
        return;
    }
    QMutableListIterator<RefPtr<EditCommandImpl> > it(m_cmds);
    while (it.hasNext())
        it.next()->reapply();

    setState(Applied);
}
