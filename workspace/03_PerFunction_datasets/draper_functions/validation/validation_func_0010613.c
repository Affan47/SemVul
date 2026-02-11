ClassifyErlangFoldPoint(
	Accessor &styler,
	int styleNext,
	int keyword_start
) {
	int lev = 0;
	if (styler.Match(keyword_start,"case")
		|| (
			styler.Match(keyword_start,"fun")
			&& (SCE_ERLANG_FUNCTION_NAME != styleNext)
			)
		|| styler.Match(keyword_start,"if")
		|| styler.Match(keyword_start,"query")
		|| styler.Match(keyword_start,"receive")
	) {
		++lev;
	} else if (styler.Match(keyword_start,"end")) {
		--lev;
	}

	return lev;
}
