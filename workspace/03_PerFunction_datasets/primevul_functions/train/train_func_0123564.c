Bool TY_(WarnMissingSIInEmittedDocType)( TidyDocImpl* doc )
{
    Bool isXhtml = doc->lexer->isvoyager;
    Node* doctype;


    if ( isXhtml )
        return no;


    if ( TY_(HTMLVersionNameFromCode)(doc->lexer->versionEmitted, isXhtml ) == NULL )
        return no;


    if ( GetSIFromVers(doc->lexer->versionEmitted) == NULL )
        return no;

    if ( (doctype = TY_(FindDocType)( doc )) != NULL
         && TY_(GetAttrByName)(doctype, "SYSTEM") == NULL )
        return yes;

    return no;
}
