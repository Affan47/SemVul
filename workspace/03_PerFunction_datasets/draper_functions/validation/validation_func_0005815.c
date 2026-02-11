isKeyword(const UnicodeString& keyword) const {
    if ( keyword == PLURAL_KEYWORD_OTHER ) {
        return true;
    }
    else {
        if (mRules==NULL) {
            return false;
        }
        else {
            return mRules->isKeyword(keyword);
        }
    }
}
