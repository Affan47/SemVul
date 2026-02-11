get_keys(void) {
    list<string> *key_list = new list<string>();
    for (pref_map_t::iterator it = _pref_map.begin();it != _pref_map.end();it++)
        key_list->push_back((*it).first);

    return key_list;
}
