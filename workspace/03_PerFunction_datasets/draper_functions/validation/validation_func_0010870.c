warning (const char *s,...) {
    char str[1024] ;
    va_list arg ;
    va_start (arg, s) ;
    vsprintf (str, s, arg) ;

    if (!currentContext->hasMacro()) {
        std::cerr << '\"' << currentContext->getFilename() << "\", line "
        	<< currentContext->getLineNumber() << ": warning: " << str << std::endl ;
    } else {
        string &macroname = currentContext->getMacroName() ;
        std::cerr << "Macro: " << macroname << ", \"" <<
        	currentContext->getFilename() << "\", line " << currentContext->getLineNumber() << ": warning: " << str << std::endl ;
        std::cerr << '\t' << line << '\n' ;
    }
}
