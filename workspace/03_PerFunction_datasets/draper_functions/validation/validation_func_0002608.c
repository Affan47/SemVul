set_skip() {

	try {
		match(LITERAL_skip);
		match(ON);
		skip_def();
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_1);
	}
}
