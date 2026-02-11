LabelEntry( const bool editable, const std::string& label, const std::string& text )
    : m_editable( editable )
{
    set_label( label );
    m_label.set_mnemonic_widget ( m_entry );
    m_entry.signal_activate().connect( sigc::mem_fun( *this, &LabelEntry::slot_entry_acivate ) );
    pack_start( m_label, Gtk::PACK_SHRINK );

    m_info.set_size_request( 0, 0 );
    m_info.set_alignment( Gtk::ALIGN_LEFT );
    m_info.set_selectable( true );

    setup();
    set_text( text );
}
