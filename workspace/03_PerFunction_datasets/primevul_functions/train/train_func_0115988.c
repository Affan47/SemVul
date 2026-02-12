CiffComponent* CiffDirectory::doAdd(CrwDirs& crwDirs, uint16_t crwTagId)
    {


        const Components::iterator b = components_.begin();
        const Components::iterator e = components_.end();

        if (!crwDirs.empty()) {
            CrwSubDir csd = crwDirs.top();
            crwDirs.pop();

            for (Components::iterator i = b; i != e; ++i) {
                if ((*i)->tag() == csd.crwDir_) {
                    cc_ = *i;
                    break;
                }
            }
            if (cc_ == 0) {

                m_ = UniquePtr(new CiffDirectory(csd.crwDir_, csd.parent_));
                cc_ = m_.get();
                add(std::move(m_));
            }

            cc_ = cc_->add(crwDirs, crwTagId);
        }
        else {

            for (Components::iterator i = b; i != e; ++i) {
                if ((*i)->tagId() == crwTagId) {
                    cc_ = *i;
                    break;
                }
            }
            if (cc_ == 0) {

                m_ = UniquePtr(new CiffEntry(crwTagId, tag()));
                cc_ = m_.get();
                add(std::move(m_));
            }
        }
        return cc_;
    }
