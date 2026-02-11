applyStylesheet( FV_View* pView,
                                             PD_RDFSemanticStylesheetHandle ss )
{
    if( !ss )
    {
        UT_DEBUGMSG(("apply stylesheet at site. format(), xmlid:%s NO SHEET\n", m_xmlid.c_str()));
        return;
    }


    UT_DEBUGMSG(("apply stylesheet at site. format(), xmlid:%s sheet:%s\n",
                 m_xmlid.c_str(), ss->name().c_str() ));
    setStylesheetWithoutReflow( ss );
    reflowUsingCurrentStylesheet( pView );
}
