CountLineEnds(cbStyledTextCtrl* control, int &linesCR, int &linesLF, int &linesCRLF)
{
    linesCR = 0;
    linesLF = 0;
    linesCRLF = 0;

    int lengthDoc = control->GetLength();
    const int maxLengthDoc = 1000000;
    char chPrev = ' ';
    char chNext = control->GetCharAt(0);
    for (int i = 0; i < lengthDoc; i++)
    {
        char ch = chNext;
        chNext = control->GetCharAt(i + 1);
        if (ch == '\r')
        {
            if (chNext == '\n')
                linesCRLF++;
            else
                linesCR++;
        }
        else if (ch == '\n')
        {
            if (chPrev != '\r')
                linesLF++;
        }
        else if (i > maxLengthDoc)
            return;

        chPrev = ch;
    }
}
