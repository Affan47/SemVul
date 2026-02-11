OnSwitchFrame(cb_unused wxCommandEvent& event)
{
    if (!IsSwitchFrameEnabled())
        return;

    if (m_list->GetSelectedItemCount() == 0)
        return;


    int index = m_list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    long realFrameNr;
    if (m_list->GetItemText(index).ToLong(&realFrameNr))
    {

        cbDebuggerPlugin *plugin = Manager::Get()->GetDebuggerManager()->GetActiveDebugger();
        if (plugin)
            plugin->SwitchToFrame(realFrameNr);
    }
    else
        cbMessageBox(_("Couldn't find out the frame number!"), _("Error"), wxICON_ERROR);
}
