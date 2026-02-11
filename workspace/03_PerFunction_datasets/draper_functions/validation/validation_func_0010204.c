adjustMarkGlyphs(LEGlyphStorage &glyphStorage, LEGlyphFilter *markFilter, LEErrorCode &success)
{
    float xAdjust = 0;
    le_int32 p, glyphCount = glyphStorage.getGlyphCount();

    if (LE_FAILURE(success)) {
        return;
    }

    if (markFilter == NULL) {
        success = LE_ILLEGAL_ARGUMENT_ERROR;
        return;
    }

    float ignore, prev;

    glyphStorage.getGlyphPosition(0, prev, ignore, success);

    for (p = 0; p < glyphCount; p += 1) {
        float next, xAdvance;

        glyphStorage.getGlyphPosition(p + 1, next, ignore, success);

        xAdvance = next - prev;
        glyphStorage.adjustPosition(p, xAdjust, 0, success);

        if (markFilter->accept(glyphStorage[p])) {
            xAdjust -= xAdvance;
        }

        prev = next;
    }

    glyphStorage.adjustPosition(glyphCount, xAdjust, 0, success);
}
