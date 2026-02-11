emit_change(change::pointer cp)
{
    long            n;

    emit_project(cp->pp);
    if (cp->bogus)
        return;
    printf(",<br>\nChange <a href=\"%s/", http_script_name());
    html_escape_string(project_name_get(cp->pp));
    n = magic_zero_decode(cp->number);
    printf(".C%ld/?menu\">%ld</a>", n, n);
}
