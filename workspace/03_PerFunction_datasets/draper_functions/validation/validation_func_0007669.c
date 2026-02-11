setChanged()
{
    if (m_node) {
        m_node->setChanged();
        return;
    }


    for (StyleBaseImpl* stylesheet = this; stylesheet; stylesheet = stylesheet->parent())
        if (stylesheet->isCSSStyleSheet()) {
            static_cast<CSSStyleSheetImpl*>(stylesheet)->doc()->updateStyleSelector();
            break;
        }
}
