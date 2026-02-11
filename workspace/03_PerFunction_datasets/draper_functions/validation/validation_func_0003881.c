prefs_filtering_free(GSList * prefs_filtering)
{
 	while (prefs_filtering != NULL) {
 		FilteringProp * filtering = (FilteringProp *)
			prefs_filtering->data;
 		filteringprop_free(filtering);
 		prefs_filtering = g_slist_remove(prefs_filtering, filtering);
 	}
}
