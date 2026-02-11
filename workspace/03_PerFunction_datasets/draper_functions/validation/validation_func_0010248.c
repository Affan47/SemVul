OnExecParameters(cb_unused wxCommandEvent& event)
{
    if (Manager::Get()->GetProjectManager()->GetActiveProject())
        Manager::Get()->GetProjectManager()->GetActiveProject()->SelectTarget(-1, true);
}
