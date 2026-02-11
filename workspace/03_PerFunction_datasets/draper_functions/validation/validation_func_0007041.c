iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        if (this->isVisible()) {
            hide();
            showMessage(tr("Welcome"), tr("KontrolPack : Access securely any remote computer."), 3000);
        } else {
            show();
        }
        break;
        case QSystemTrayIcon::DoubleClick:
        break;
    case QSystemTrayIcon::MiddleClick:
        QMessageBox::information(this, tr("About KontrolPack"), tr("KontrolPack : Secure remote access."));
        break;
    default:
        ;
    }
}
