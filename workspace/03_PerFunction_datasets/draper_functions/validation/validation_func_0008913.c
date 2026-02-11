setCryptedPassword(const QVariant &val)
{
    if (val.toString() == value(Table_USERS, USER_PASSWORD).toString())
        return;
    d->m_Table_Field_Value[Table_USERS].insert(USER_PASSWORD, val);
    d->m_PasswordChanged = true;
    d->m_Modified = true;
}
