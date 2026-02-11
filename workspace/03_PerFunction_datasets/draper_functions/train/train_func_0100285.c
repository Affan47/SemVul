setActiveNode(const DOM::Node &node)
{
    if (!d->m_doc || !d->m_view)
        return;


    d->m_doc->setFocusNode(node.handle());


    QRect rect  = node.handle()->getRect();
    d->m_view->ensureVisible(rect.right(), rect.bottom());
    d->m_view->ensureVisible(rect.left(), rect.top());
}
