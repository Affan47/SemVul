std::ostream &operator <<(std::ostream &os, const HttpStateData::ReuseDecision &d)
{
    static const char *ReuseMessages[] = {
        "do not cache and do not share",
        "cache positively and share",
        "cache negatively and share",
        "do not cache but share"
    };

    assert(d.answer >= HttpStateData::ReuseDecision::reuseNot &&
           d.answer <= HttpStateData::ReuseDecision::doNotCacheButShare);
    return os << ReuseMessages[d.answer] << " because " << d.reason <<
           "; HTTP status " << d.statusCode << " " << *(d.entry);
}
