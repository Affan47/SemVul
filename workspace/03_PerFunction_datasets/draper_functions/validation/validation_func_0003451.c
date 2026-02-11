cancelSearch()
{
    setText("");
    QRect cr = rect();
    m_Completer->complete(cr);
}
