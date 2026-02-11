installed_truetype(const String &ttf_filename, bool allow_generate, ErrorHandler *errh)
{
    String file = pathname_filename(ttf_filename);

#if HAVE_KPATHSEA
    if (!(force && allow_generate && ttf_filename && ttf_filename != "-" && getodir(O_TRUETYPE, errh))) {
	if (String path = kpsei_string(kpsei_find_file(file.c_str(), KPSEI_FMT_TRUETYPE))) {
	    if (path == "./" + file || path == file) {
		if (verbose)
		    errh->message("ignoring TrueType file %s found with kpathsea in %<.%>", path.c_str());
	    } else {
		if (verbose)
		    errh->message("TrueType file %s found with kpathsea at %s", file.c_str(), path.c_str());
		return path;
	    }
	}
    }
#endif


    if (allow_generate && ttf_filename && ttf_filename != "-" && getodir(O_TRUETYPE, errh)) {
	String installed_ttf_filename = odir[O_TRUETYPE] + "/" + file;
	if (installed_ttf_filename.find_left('\'') >= 0 || installed_ttf_filename.find_left('\"') >= 0)
	    return String();

	int retval;
	if (!same_filename(ttf_filename, installed_ttf_filename)) {
	    String command = "cp " + shell_quote(ttf_filename) + " " + shell_quote(installed_ttf_filename);
	    retval = mysystem(command.c_str(), errh);
	    if (retval == 127)
		errh->error("could not run %<%s%>", command.c_str());
	    else if (retval < 0)
		errh->error("could not run %<%s%>: %s", command.c_str(), strerror(errno));
	    else if (retval != 0)
		errh->error("%<%s%> failed", command.c_str());
	} else {
	    if (verbose)
		errh->message("TrueType file %s already located in output directory", installed_ttf_filename.c_str());
	    retval = 0;
	}

	if (retval == 0) {
	    update_odir(O_TRUETYPE, installed_ttf_filename, errh);
	    return installed_ttf_filename;
	}
    }

    return String();
}
