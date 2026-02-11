setStorableData(const QVariant &data)
{

    if (!data.isValid())
        return;
    m_OriginalValue = data.toString();
    if (m_OriginalValue.simplified().isEmpty()
            && !patient()->uuid().isEmpty())
        populateWithPatientData();
    else
        m_Widget->setNumberWithControlKey(m_OriginalValue);

}
