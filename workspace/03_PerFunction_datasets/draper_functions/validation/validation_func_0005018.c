getAnnotations (Operand *dest, Operand *var) {
    map *m = new map();
    Variable *v = static_cast<Variable*>(var->val.ptr);
    AnnotationList &annotations = v->annotations;
    for (AnnotationList::iterator i = annotations.begin() ; i != annotations.end() ; i++) {
        Annotation *a = *i;
        map *actualmap = new map();
        Scope::VarMap::iterator var;
        Interface *iface = a->iface;
        for (var = iface->variables.begin() ; var != iface->variables.end() ; var++) {
            std::string tagname = var->first.str;
            if (tagname[0] == '.') {
                std::string varname = tagname.substr(1);

                Node *node = getBlockAnnotationValue (a, (Tag*)var->second, varname);
                if (node == NULL) {
                    actualmap->insert (Value(varname), Value());
                } else {
                    node = new Node (aikido, RETURN, node) ;
                    codegen::CodeSequence *code = aikido->codegen->generate (node) ;
                    execute (code) ;
                    Value result = retval ;
                    retval.destruct() ;
                    actualmap->insert (Value (varname), result);
                }
            }
        }

        m->insert (Value (a->iface->name.substr(1)), Value (actualmap));
    }
    set (dest, m);
}
