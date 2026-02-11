ParseFile(const char* fname, AbstractSystem* system, int variation)
{
    CFDGImpl* pCfdg = NULL;
    for (int version = 2; version <= 4; ++version) {
        if (pCfdg == NULL)
            pCfdg = new CFDGImpl(system);
        Builder b(pCfdg, variation);

        yy::Scanner lexer;
        b.lexer = &lexer;
        lexer.driver = &b;
        lexer.startToken = version == 2 ? yy::CfdgParser::token::CFDG2 :
                                          yy::CfdgParser::token::CFDG3;
        b.mCompilePhase = version < 4 ? 1 : 2;
        b.mWant2ndPass = version == 3;

        yy::CfdgParser parser(b);
        istream* input = system->openFileForRead(fname);
        if (!input || !input->good()) {
            delete input;
            input = 0;
            system->error();
            system->message("Couldn't open rules file %s", fname);
            return 0;
        }

        pCfdg->fileNames.push_back(fname);
        b.m_currentPath = &(pCfdg->fileNames.back());
        b.m_basePath = b.m_currentPath;
        b.m_filesToLoad.push(b.m_currentPath);
        b.m_streamsToLoad.push(input);
        b.m_includeNamespace.push(false);

        if (version == 2)
            system->message("Reading rules file %s", fname);

        lexer.yyrestart(input);


        int yyresult = 0;
        try {
            yyresult = parser.parse();
        } catch (CfdgError err) {
            system->syntaxError(err);
            return 0;
        }

        if (b.mErrorOccured)
            return 0;
        if (yyresult == 0) {
            pCfdg->rulesLoaded();
            if (b.mErrorOccured)
                return 0;
            if (b.mWant2ndPass) {
                pCfdg = new CFDGImpl(pCfdg);
                system->message("Compiling 2nd phase");
                continue;
            }
            b.m_CFDG = 0;
            break;
        }
        if (lexer.maybeVersion == 0 ||
            lexer.maybeVersion == (version == 2 ? yy::CfdgParser::token::CFDG2 :
                                                  yy::CfdgParser::token::CFDG3))
            return 0;
        system->message("Restarting as a version 3 design");
        pCfdg = NULL;
    }

    system->message("%d rules loaded", pCfdg->numRules());

    return pCfdg;
}
