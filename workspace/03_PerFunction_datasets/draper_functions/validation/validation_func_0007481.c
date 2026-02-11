render()
{
    const WidgetLookFeel& wlf = getLookNFeel();

    renderBaseImagery(wlf);


    Font* const font = d_window->getFont();
    if (!font)
        return;

    String visual_text;
    setupVisualString(visual_text);

    const ImagerySection& caret_imagery = wlf.getImagerySection("Carat");


    const Rect text_area(wlf.getNamedArea("TextArea").getArea().getPixelRect(*d_window));

    const size_t caret_index = getCaretIndex(visual_text);
    const float extent_to_caret = font->getTextExtent(visual_text.substr(0, caret_index));
    const float caret_width = caret_imagery.getBoundingRect(*d_window, text_area).getWidth();
    const float text_extent = font->getTextExtent(visual_text);
    const float text_offset = calculateTextOffset(text_area, text_extent, caret_width, extent_to_caret);

#ifdef CEGUI_BIDI_SUPPORT
    renderTextBidi(wlf, visual_text, text_area, text_offset);
#else
    renderTextNoBidi(wlf, visual_text, text_area, text_offset);
#endif


    d_lastTextOffset = text_offset;

    renderCaret(caret_imagery, text_area, text_offset, extent_to_caret);
}
