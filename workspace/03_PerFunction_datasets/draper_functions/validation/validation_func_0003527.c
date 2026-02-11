toggleMenubar()
{
    if(m_showMenubarAction->isChecked())
        menuBar()->show();
    else if(KMessageBox::warningContinueCancel(this,
            i18n("Are you sure you want to hide the menubar? The current shortcut to show it again is %1.",
                 m_showMenubarAction->shortcut().toString(QKeySequence::NativeText)),
            i18n("Hide Menubar"),
            KStandardGuiItem::cont(),
            KStandardGuiItem::cancel(),
            QLatin1String("MenubarWarning")) == KMessageBox::Continue)
        menuBar()->hide();
    else
      m_showMenubarAction->setChecked(true);
}
