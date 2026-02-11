newDevType()
{
    if (ui.deviceTypeComboBox->currentText().toStdString().compare(0,4,"3390") == 0)
        ui.linuxCheckBox->setEnabled(true);
    else
    {
        ui.linuxCheckBox->setEnabled(false);
        ui.linuxCheckBox->setChecked(false);
    }
    setSizeValue();
}
