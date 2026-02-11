test_parsing_xspf_genre (void)
{
	char *uri;
	uri = get_relative_uri (TEST_SRCDIR "playlist.xspf");
	g_assert_cmpstr (parser_test_get_entry_field (uri, TOTEM_PL_PARSER_FIELD_GENRE), ==, "Test Genre");
	g_free (uri);

	uri = get_relative_uri (TEST_SRCDIR "decrypted-amazon-track.xspf");
	g_assert_cmpstr (parser_test_get_entry_field (uri, TOTEM_PL_PARSER_FIELD_GENRE), ==, "Dance & DJ/House");
	g_free (uri);
}
