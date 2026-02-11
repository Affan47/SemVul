checkDefns() {
    List tcs;
    Module thisModule = lastModule();
    staticAnalysis(RESET);

    setCurrModule(thisModule);


    mapProc(checkQualImport,  module(thisModule).modAliases);
    mapProc(checkUnqualImport,unqualImports);

    if ((thisModule!=modulePrelude && thisModule!=moduleUserPrelude)
	&& isNull(cellAssoc(moduleUserPrelude,unqualImports))
	&& isNull(cellRevAssoc(moduleUserPrelude,module(thisModule).modAliases)) ) {
	addUnqualImport(moduleUserPrelude,mkCon(textUserPrelude),DOTDOT);
    }
    map1Proc(checkImportList, FALSE, unqualImports);
    mapProc(checkQualImportList, module(thisModule).qualImports);


    fixupImportExports(module(currentModule).modImports);


    linkPreludeTC();
    mapProc(checkTyconDefn,tyconDefns);
    checkSynonyms(tyconDefns);
    mapProc(checkClassDefn,classDefns);
    tcs = tcscc(tyconDefns,classDefns);

    mapProc(kindTCGroup,tcs);
    mapProc(visitClass,classDefns);
    mapProc(extendFundeps,classDefns);


    mapProc(checkClassDefn2_,tcs);
    mapProc(addMembers,classDefns);
    linkPreludeCM();

    mapOver(checkPrimDefn,primDefns);

    instDefns = rev(instDefns);
    mapProc(checkInstDefn,instDefns);

    setCurrModule(thisModule);
    mapProc(addRSsigdecls,typeInDefns);
    valDefns   = eqnsToBindings(valDefns,tyconDefns,classDefns,primDefns);
    mapProc(allNoPrevDef,valDefns);
    mapProc(addDerivImp,derivedInsts);
    deriveContexts(derivedInsts);
    instDefns  = appendOnto(instDefns,derivedInsts);
    checkDefaultDefns();

    tyconDefns = NIL;
    primDefns  = NIL;

    if (nonNull(foreignImports) || nonNull(foreignExports)) {


        Bool need_stubs = foreignNeedStubs(foreignImports, foreignExports);

        if (generate_ffi && need_stubs) {
            foreignHeader(scriptFile);
        }
        mapProc(checkForeignImport,foreignImports);
        mapProc(checkForeignExport,foreignExports);
        if (generate_ffi && need_stubs) {
            foreignFooter(scriptFile, module(thisModule).text,
			  foreignImports, foreignExports);
        }
	if (need_stubs && (generate_ffi || !generateFFI)) {
	  needPrims(0, NULL);
	  mapProc(linkForeign,foreignImports);
#if 0
	  mapProc(linkForeign,foreignExports);
#endif
	}


        foreignImports = NIL;
    }


    module(thisModule).exports = checkExports(module(thisModule).exports);

    mapProc(checkTypeIn,typeInDefns);

    clearScope();
    withinScope(valDefns);
    valDefns = topDependAnal(valDefns);
    linkPreludeFuns();
    mapProc(depDefaults,classDefns);
    mapProc(depInsts,instDefns);
    leaveScope();


    evalDefaults = defaultDefns;


    staticAnalysis(RESET);
}
