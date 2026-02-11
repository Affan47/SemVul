insertTab(SWF::TextRecord& rec, boost::int32_t& x, float scale)
{

    const int space = 32;
    int index = rec.getFont()->get_glyph_index(space, _embedFonts);
    if (index == -1) {
        IF_VERBOSE_MALFORMED_SWF (
          log_error(_("TextField: missing glyph for space char (needed "
                  "for TAB). Make sure DisplayObject shapes for font "
                  "%s are being exported into your SWF file."),
                rec.getFont()->name());
        );
    }
    else {

		std::vector<int> tabStops = _tabStops;

        std::sort(_tabStops.begin(), _tabStops.end());

        if (!_tabStops.empty()) {
            int tab = _tabStops.back() + 1;

            for (size_t i = 0; i < tabStops.size(); ++i) {
                if (tabStops[i] > x) {
                    if((tabStops[i] - x) < tab) {
                        tab = tabStops[i] - x;
                    }
				}

            }


			if (tab != _tabStops.back() + 1) {
				SWF::TextRecord::GlyphEntry ge;
				ge.index = rec.getFont()->get_glyph_index(32, _embedFonts);
				ge.advance = tab;
				rec.addGlyph(ge);
				x+=ge.advance;
			}
        }
        else {
            SWF::TextRecord::GlyphEntry ge;
            ge.index = index;
            ge.advance = scale * rec.getFont()->get_advance(index,
                    _embedFonts);

            const int tabstop = 4;
            rec.addGlyph(ge, tabstop);
            x += ge.advance * tabstop;
        }
    }
}
