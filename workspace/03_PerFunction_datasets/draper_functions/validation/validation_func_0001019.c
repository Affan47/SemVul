attribute(const String& attributeName) const
{
    static const String null;

    for(std::list<Attribute>::const_iterator it = _attributes.begin(); it != _attributes.end(); ++it) {
        if(it->name() == attributeName) {
            return it->value();
        }
    }

    return null;
}
