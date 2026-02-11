GetTextSize(Uint16& w, Uint16& h, const std::string& text) {
	if(text.empty()) {
		if(_mid->widthText != TXT_HEIGHT_UNDEF) {
			w = _mid->widthText;
			h = _mid->heightText;
			return;
		}
		GetTextSize(w, h, my_text, _mid->font);
		_mid->widthText = w;
		_mid->heightText = h;
		return;
	}

	GetTextSize(w, h, text, _mid->font);
}
