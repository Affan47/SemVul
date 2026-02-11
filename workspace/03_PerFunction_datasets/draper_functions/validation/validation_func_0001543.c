find_profile_by_name(const char *name) {
    if (strcmp(name, PROFILE_NAME_DEFAULT) == 0)
        return _default_profile;

    for (profile_map_t::iterator it1 = _usr_profiles.begin();it1 != _usr_profiles.end();it1++) {
        if (strcmp(name, (*it1).second->get_name()) == 0)
            return (*it1).second;
    }

    for (profile_map_t::iterator it2 = _add_profiles.begin();it2 != _add_profiles.end();it2++) {
        if (strcmp(name, (*it2).second->get_name()) == 0)
            return (*it2).second;
    }

    return NULL;
}
