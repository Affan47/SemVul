remove_page( const int page, const bool adjust_tab )
{
    SKELETON::TabLabel* tablabel = m_notebook_tab.get_tablabel( page );

    m_notebook_tab.remove_tab( page, adjust_tab );
    m_notebook_view.remove_page( page );

    if( tablabel ) delete tablabel;

    m_tooltip.hide_tooltip();

    if( ! get_n_pages() ) m_bt_tabswitch.hide_button();
}
