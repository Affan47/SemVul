bool Scanner::include(const std::string &filename)
{

    DASSERT(!files.empty());
    const std::string &parent = files.back()->escaped_name;


    for (size_t i = 0; i < files.size(); ++i) {
        Input *in = files[i];
        if (in->so >= cur) {

            fseek(in->file, in->so - in->eo, SEEK_CUR);
            in->so = in->eo = ENDPOS;
        }
        else if (in->eo >= cur) {

            fseek(in->file, cur - in->eo, SEEK_CUR);
            in->eo = cur - 1;
        }
        else {

            break;
        }
    }


    if (!open(filename, &parent)) {
        return false;
    }


    lim = cur = mar = ctx = tok = ptr = pos = bot + BSIZE;
    eof = NULL;
    return fill(BSIZE);
}
