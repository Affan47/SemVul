PlaceBookmark(ExState &State) {
    char name[256] = "";
    EPoint P = CP;

    P.Row = VToR(P.Row);

    if (State.GetStrParam(View, name, sizeof(name)) == 0)
        if (View->MView->Win->GetStr("Place Bookmark", sizeof(name), name, HIST_BOOKMARK) == 0) return 0;
    return PlaceUserBookmark(name, P);
}
