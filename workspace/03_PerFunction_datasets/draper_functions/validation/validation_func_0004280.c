multi_common_split_text()
{
	int	n_lines, i;
	int	n_chars[MAX_BRIEF_LINES];
	char	*p_str[MAX_BRIEF_LINES];

	n_lines = split_str(Multi_common_all_text, Multi_common_text_coords[gr_screen.res][2], n_chars, p_str, MULTI_COMMON_TEXT_MAX_LINES, MULTI_COMMON_TEXT_META_CHAR);
	Assert(n_lines != -1);

	for ( i = 0; i < n_lines; i++ ) {


		strncpy(Multi_common_text[i], p_str[i], n_chars[i]);
		Multi_common_text[i][n_chars[i]] = 0;
		drop_leading_white_space(Multi_common_text[i]);
	}

	Multi_common_top_text_line = 0;
	Multi_common_num_text_lines = n_lines;
}
