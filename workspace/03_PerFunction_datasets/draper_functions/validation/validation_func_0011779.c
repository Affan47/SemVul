init(void* args)
{

	DMPlugin::init(args);


	upperlimit = cv["maxdownloadsize"].toOffset() * 1024;
	if (upperlimit <= o.max_content_filecache_scan_size)
		upperlimit = 0;
#ifdef DGDEBUG
	std::cout << "Upper download limit: " << upperlimit << std::endl;
#endif

	String fname(cv["template"]);
	if (fname.length() > 0) {

		fname = o.languagepath + fname;
		return progresspage.readTemplateFile(fname.toCharArray(), "-FILENAME-|-FILESIZE-|-SERVERIP-") ? 0 : -1;
	} else {

		if (!is_daemonised)
			std::cerr << "Template not specified for fancy download manager" << std::endl;
		syslog(LOG_ERR, "Template not specified for fancy download manager");
		return -2;
	}
}
