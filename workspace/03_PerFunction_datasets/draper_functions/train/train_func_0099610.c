tracker_store_sparql_update_data_free (gpointer _data) {
	TrackerStoreSparqlUpdateData* _data_;
	_data_ = _data;
#line 22 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
	_g_free0 (_data_->sparql);
#line 22 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
	_g_free0 (_data_->client_id);
#line 22 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
	g_slice_free (TrackerStoreSparqlUpdateData, _data_);
#line 2385 "tracker-store.c"
}
