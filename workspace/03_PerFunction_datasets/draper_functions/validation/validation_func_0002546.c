deny_std() {

	try {
		match(DENY);
		if ( inputState->guessing==0 ) {
#line 303 "iosacl.g"

			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newPolicyRule();
			importer->action = "deny";
			*dbg << LT(1)->getLine() << ":" << " deny   ";

#line 801 "IOSCfgParser.cpp"
		}
		rule_std();
		match(NEWLINE);
		if ( inputState->guessing==0 ) {
#line 310 "iosacl.g"

			importer->pushRule();

#line 810 "IOSCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_2);
		} else {
			throw;
		}
	}
}
