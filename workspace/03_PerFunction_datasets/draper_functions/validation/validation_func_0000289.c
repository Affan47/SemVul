Delete (
    TextDisplay* display, int line, int index, int count
) {
    IntCoord left, right;
    int shift;
    Size(Math::max(lastchar, index));
    count = Math::max(0, Math::min(count, lastchar-index+1));
    int src = index + count;
    int dst = index;
    int len = lastchar - (index + count) + 1;
    if (display->canvas != nil) {
        left = display->Left(line, index + count);
        right = Math::min(display->Right(line, lastchar + 1), display->xmax);
    }
    Memory::copy(text + src, text + dst, len);
    Memory::copy(attr + src, attr + dst, len);
    Memory::zero(text + lastchar + 1 - count, count);
    Memory::zero(attr + lastchar + 1 - count, count);
    lastchar -= count;
    if (display->canvas != nil) {
        if (strchr(text+index, '\t') != nil) {
            Draw(display, line, index, lastchar+1);
        } else {
            shift = left - display->Left(line, index);
            IntCoord bottom = display->Base(line);
            IntCoord top = display->Top(line);
            if (left <= right) {
                display->painter->Copy(
                    display->canvas, left, bottom, right, top,
                    display->canvas, left-shift, bottom
                );
            }
            if (shift > 0) {
                int last = display->LineIndex(line, right-shift+1, false);
                Draw(display, line, last, lastchar + 1);
            }
        }
    }
}
