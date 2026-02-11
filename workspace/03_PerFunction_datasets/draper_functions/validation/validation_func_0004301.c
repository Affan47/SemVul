preferredDetail(const QString& actionName) const
{

    if (actionName.isEmpty())
        return QContactDetail();

    if (!d->m_preferences.contains(actionName))
        return QContactDetail();

    QContactDetail retn;
    int detId = d->m_preferences.value(actionName);
    for (int i = 0; i < d->m_details.size(); i++) {
        QContactDetail det = d->m_details.at(i);
        if (det.d->m_id == detId) {

            retn = det;
            break;
        }
    }

    return retn;
}
