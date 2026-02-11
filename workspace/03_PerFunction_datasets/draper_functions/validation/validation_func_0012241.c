recomputeNamespaceInfo()
{
    assert (!m_namespaces);

    m_namespaces = new QList<CSSNamespaceRuleImpl*>;
    m_defaultNamespace = NamespaceName::fromId(anyNamespace);


    for (int i = 0; i < m_lstChildren->count(); ++i) {
        StyleBaseImpl* b = m_lstChildren->at(i);
        if (b->isRule() && static_cast<CSSRuleImpl*>(b)->type() == DOM::CSSRule::NAMESPACE_RULE) {
            CSSNamespaceRuleImpl* nr = static_cast<CSSNamespaceRuleImpl*>(b);
            DOM::DOMString prefix = nr->prefix();
            DOM::DOMString uri    = nr->namespaceURI();

            if (uri.isNull())
                continue;

            if (nr->isDefault())
                m_defaultNamespace = NamespaceName::fromString(uri);

            m_namespaces->append(nr);
        }
    }
}
