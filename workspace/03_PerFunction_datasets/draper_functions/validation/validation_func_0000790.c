dorequire(filename1, o, params)
    FILE *o;
    STR filename1;
    STR params; {

    FILENAME filename, script, component;

    if (params && !*params) params = NULL;

    makecache(filename1, filename, "htpm");
    makecache(filename1, component, "htpc");
    makecache(filename1, script, "ht.pl");

    if (depend(filename, component) > 0 || fit(filename, component, 0)) {
        makecomponent(filename);
        fit(filename, component, 1);
    }
    if (depend(script, filename) > 0 || fit(script, filename, 0)) compile(filename, script);
    if (params) beforerequire(o, params);
    outf(o, "do \"%s\";", qualify(script, 0));
    if (params) outf(o, "&HTML::HTPL::Sys::popvars;");
}
