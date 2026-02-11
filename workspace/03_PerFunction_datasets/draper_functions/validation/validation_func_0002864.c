get_popupmenu( const std::string& url )
{
    Gtk::Menu* popupmenu = NULL;
    if( ! url.empty() ){

        std::list< Gtk::TreeModel::iterator > list_it = get_treeview().get_selected_iterators();
        if( list_it.size() == 1 ){

            const int type = path2type( *( get_treeview().get_selection()->get_selected_rows().begin() ) );

            if( type == TYPE_VBOARD ) popupmenu = id2popupmenu( "/popup_menu_history_vboard" );
            else popupmenu = id2popupmenu( "/popup_menu_history" );
        }
        else popupmenu = id2popupmenu(  "/popup_menu_history_mul" );
    }

    return popupmenu;
}
