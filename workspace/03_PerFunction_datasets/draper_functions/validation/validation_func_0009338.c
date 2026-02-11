OnUpdateUI(cb_unused wxUpdateUIEvent& event)
{
    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);
    size_t page = lb->GetSelection();

    XRCCTRL(*this, "wxID_OK", wxButton)->Enable((page != lb->GetPageCount() - 1 && GetSelectedTemplate()) || SelectedUserTemplate());
}
