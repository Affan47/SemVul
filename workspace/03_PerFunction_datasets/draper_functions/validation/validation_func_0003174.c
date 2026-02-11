setCurrentPatient(const QModelIndex &index)
{

    if (!index.isValid()) {
        d->m_CurrentPatientIndex = index;
        d->m_CurrentPatientUuid.clear();
        LOG("Removed current patient");
        return true;
    }

    const QString &patientUuid = this->patientUuid(index);
    if (patientUuid.isEmpty()) {
        LOG_ERROR(QString("Empty patient Uuid. Index(%1,%2,%3)").arg(index.row()).arg(index.column()).arg(index.model()->objectName()));
        return false;
    }

    if (patientUuid == d->m_CurrentPatientUuid)
        return true;

    d->m_CurrentPatientUuid = patientUuid;
    d->m_CurrentPatientIndex = index;
    LOG("setCurrentPatient: " + patientUuid);
    return true;
}
