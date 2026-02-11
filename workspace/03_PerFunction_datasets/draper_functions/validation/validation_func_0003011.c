operator<<(QDBusArgument &argument, const AuthInfo &a)
{
    argument.beginStructure();
    argument << (quint8)1
             << a.url.url() << a.username << a.password << a.prompt << a.caption
             << a.comment << a.commentLabel << a.realmValue << a.digestInfo
             << a.verifyPath << a.readOnly << a.keepPassword << a.modified
             << a.d->extraFields;
    argument.endStructure();
    return argument;
}
