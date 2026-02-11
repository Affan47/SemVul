parseDeclaration( DOM::CSSStyleDeclarationImpl *declaration, const DOM::DOMString &string)
{
#ifdef CSS_DEBUG
    kDebug( 6080 ) << "CSSParser::parseDeclaration:"
                    << " value='" << string.string() << "'" << endl;
#endif

    styleElement  = declaration->stylesheet();
    styleDocument = 0;

    setupParser("@-khtml-decls{", string, "} ");
    runParser();

    delete rule;
    rule = 0;

    bool ok = false;
    if ( numParsedProperties ) {
        ok = true;
        addParsedProperties(declaration, parsedProperties, numParsedProperties);
        numParsedProperties = 0;
    }

    return ok;
}
