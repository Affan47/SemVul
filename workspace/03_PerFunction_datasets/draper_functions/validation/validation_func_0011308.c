addBoard(const Glib::ustring &name, const libhexx::Layout &l)
{

    if(data.find(name) != data.end())
        return true;


    Gtk::TreeModel::Children::iterator iter = lstore->children().begin();
    while(iter != lstore->children().end())
    {
        if(name < (*iter)[colRec.col_name])
            break;

        ++iter;
    }

    Gtk::TreeModel::Row row;

    if(iter == lstore->children().end())
        row = *(lstore->append());
    else
        row = *(lstore->insert(iter));

    row[colRec.col_name] = name;

    data[name] = l;

    return false;
}
