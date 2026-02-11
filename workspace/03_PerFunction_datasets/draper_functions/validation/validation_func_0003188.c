EditorLinesAddedOrRemoved(cbEditor* editor, int startline, int lines)
{


    if (!editor || lines == 0)
        return;

    const wxString& filename = editor->GetFilename();

    std::vector<int> breakpoints_for_file;
    int count = GetBreakpointsCount();
    for (int ii = 0; ii < count; ++ii)
    {
        const cb::shared_ptr<cbBreakpoint> &b = GetBreakpoint(ii);

        if (b->GetLocation() == filename)
        {
            breakpoints_for_file.push_back(ii);
        }
    }

    if (lines < 0)
    {


        lines = -lines;
        int endline = startline + lines - 1;

        std::vector<cb::shared_ptr<cbBreakpoint> > to_remove;

        for (std::vector<int>::iterator it = breakpoints_for_file.begin(); it != breakpoints_for_file.end(); ++it)
        {
            const cb::shared_ptr<cbBreakpoint> &b = GetBreakpoint(*it);
            if (b->GetLine() > endline)
                ShiftBreakpoint(*it, -lines);
            else if (b->GetLine() >= startline && b->GetLine() <= endline)
                to_remove.push_back(b);
        }

        for (std::vector<cb::shared_ptr<cbBreakpoint> >::iterator it = to_remove.begin(); it != to_remove.end(); ++it)
            DeleteBreakpoint(*it);
    }
    else
    {
        for (std::vector<int>::iterator it = breakpoints_for_file.begin(); it != breakpoints_for_file.end(); ++it)
        {
            const cb::shared_ptr<cbBreakpoint> &b = GetBreakpoint(*it);
            if (b->GetLine() > startline)
                ShiftBreakpoint(*it, lines);
        }
    }
}
