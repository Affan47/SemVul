FindAge(const plString& name) {
    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai)->getAgeName() == name)
            return *ai;
        ai++;
    }
    return NULL;
}
