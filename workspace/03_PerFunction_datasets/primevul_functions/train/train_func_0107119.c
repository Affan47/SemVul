void CiffDirectory::doRemove(CrwDirs& crwDirs, uint16_t crwTagId)
    {
        const Components::iterator b = components_.begin();
        const Components::iterator e = components_.end();
        Components::iterator i;

        if (!crwDirs.empty()) {
            CrwSubDir csd = crwDirs.top();
            crwDirs.pop();

            for (i = b; i != e; ++i) {
                if ((*i)->tag() == csd.crwDir_) {

                    (*i)->remove(crwDirs, crwTagId);
                    if ((*i)->empty()) components_.erase(i);
                    break;
                }
            }
        }
        else {

            for (i = b; i != e; ++i) {
                if ((*i)->tagId() == crwTagId) {

                    delete *i;
                    components_.erase(i);
                    break;
                }
            }
        }
    }
