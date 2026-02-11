recalcMinMaxWidths()
{
    KHTMLAssert( m_recalcMinMax );

#ifdef DEBUG_LAYOUT
    kDebug( 6040 ) << renderName() << " recalcMinMaxWidths() this=" << this;
#endif

    RenderObject *child = firstChild();
    int cmin=0;
    int cmax=0;

    while( child ) {
        bool test = false;
        if ( ( m_minMaxKnown && child->m_recalcMinMax ) || !child->m_minMaxKnown ) {
            cmin = child->minWidth();
            cmax = child->maxWidth();
            test = true;
        }
        if ( child->m_recalcMinMax )
            child->recalcMinMaxWidths();
        if ( !child->m_minMaxKnown )
            child->calcMinMaxWidth();
        if ( m_minMaxKnown && test && (cmin != child->minWidth() || cmax != child->maxWidth()) )
            m_minMaxKnown = false;
        child = child->nextSibling();
    }


    if ( ( !isInline() || isReplacedBlock() ) && childrenInline() )
        m_minMaxKnown = false;

    if ( !m_minMaxKnown )
        calcMinMaxWidth();
    m_recalcMinMax = false;
}
