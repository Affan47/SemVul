slotUpdateComboBoxLabels( int value )
{
    m_unitSelection->setItemText(0, i18np("second", "seconds", value));
    m_unitSelection->setItemText(1, i18np("minute", "minutes", value));
    m_unitSelection->setItemText(2, i18np("hour", "hours", value));
    m_unitSelection->setItemText(3, i18np("day", "days", value));
    m_unitSelection->setItemText(4, i18np("week", "weeks", value));
    m_unitSelection->setItemText(5, i18np("month", "months", value));
    m_unitSelection->setItemText(6, i18np("year", "years", value));
}
