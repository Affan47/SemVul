Append(const wxString& text, int type) {
    long count  = GETLB(wid)->GetItemCount();
    long itemID  = GETLB(wid)->InsertItem(count, wxEmptyString);
    long idx = -1;
    GETLB(wid)->SetItem(itemID, 1, text);
    maxStrWidth = wxMax(maxStrWidth, text.length());
    if (type != -1) {
        wxCHECK_RET(imgTypeMap, wxT("Unexpected NULL imgTypeMap"));
        idx = imgTypeMap->Item(type);
    }
    GETLB(wid)->SetItemImage(itemID, idx, idx);
}
