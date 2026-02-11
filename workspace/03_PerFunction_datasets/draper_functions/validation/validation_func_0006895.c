print_xml(FILE *out, bool constrained, const string &blob)
{
    ostringstream oss;
    print_xml_writer(oss, constrained, blob);
    fwrite(oss.str().data(), 1, oss.str().length(), out);
}
