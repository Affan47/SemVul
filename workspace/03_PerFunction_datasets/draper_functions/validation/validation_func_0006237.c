setButtonText(QDialogButtonBox::StandardButton sb, const QString & text)
{
    m_buttonNames[sb] = text;
    if (QPushButton * pButton = m_buttonBox->button(sb))
        pButton->setText(text);
}
