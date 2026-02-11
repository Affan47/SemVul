operator<< (const ControlToken ct)
{
    switch (ct)
    {
        case NewLine:
            addNewLine();
            break;
        case IncIndent:
            ++indentLevelM;
            break;
        case DecIndent:
            if (indentLevelM)
                --indentLevelM;
            break;
        case DisableLineWrapping:
            lineWrappingM = false;
            break;
        case EnableLineWrapping:
            if (maxLineLengthM)
                lineWrappingM = true;
            break;
        default:
            wxASSERT(false);
            break;
    }
    return (*this);
}
