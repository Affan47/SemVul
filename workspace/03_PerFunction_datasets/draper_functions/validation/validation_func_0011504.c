stealRockerGesture(KShortcutsEditorItem *item, const KRockerGesture &gst)
{
    QString title = i18n("Key Conflict");
    QString message = i18n("The '%1' rocker gesture has already been allocated to the \"%2\" action.\n"
                           "Do you want to reassign it from that action to the current one?",
                           gst.rockerName(), item->m_action->text());

    if (KMessageBox::warningContinueCancel(q, message, title, KGuiItem(i18n("Reassign")))
        != KMessageBox::Continue)
        return false;

    item->setRockerGesture(KRockerGesture());
    return true;
}
