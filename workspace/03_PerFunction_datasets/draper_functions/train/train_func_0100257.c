__lambda71_ (GmpcBrowsersMetadata* self, GmpcWidgetsSonglist* source, mpd_Song* song) {
	mpd_Song* _tmp0_;
	const gchar* _tmp1_;
	g_return_if_fail (source != NULL);
	g_return_if_fail (song != NULL);
	_tmp0_ = song;
	_tmp1_ = _tmp0_->artist;
	if (_tmp1_ != NULL) {
		mpd_Song* _tmp2_;
		const gchar* _tmp3_;
		_tmp2_ = song;
		_tmp3_ = _tmp2_->artist;
		gmpc_browsers_metadata_set_artist (self, _tmp3_);
	}
}
