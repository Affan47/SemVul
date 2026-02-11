insertData( const unsigned long offset, const DOMString &arg, int &exceptioncode )
{
    exceptioncode = 0;
    checkCharDataOperation(offset, exceptioncode);
    if (exceptioncode)
        return;

    DOMStringImpl *oldStr = str;
    str = str->copy();
    str->ref();
    str->insert(arg.impl, offset);
    if (m_render)
      (static_cast<RenderText*>(m_render))->setText(str);
    setChanged(true);

    dispatchModifiedEvent(oldStr);
    oldStr->deref();
}
