open_pixmap_from_file(const std::string& pixmapname)
{
    std::string filename = std::string(IMAGE_INSTALL_DIR) + tileset + pixmapname + ".png";
    std::string defaultfilename = std::string(IMAGE_INSTALL_DIR) + pixmapname + ".png";
    Glib::RefPtr<Gdk::Pixbuf> ret;

    try
    {
	if (!Glib::file_test(filename, Glib::FILE_TEST_EXISTS) &&
		Glib::file_test(defaultfilename, Glib::FILE_TEST_EXISTS))
	    ret = Gdk::Pixbuf::create_from_file(defaultfilename);
	else
	    ret = Gdk::Pixbuf::create_from_file(filename);
    }

    catch(Glib::FileError e)
    {
        std::cout << "Could not open image: " << filename << ", aborting!\n";
        exit(-1);
    }

    catch(Gdk::PixbufError)
    {
        std::cout << "Could not parse image: " << filename << ", aborting!\n";
        exit(-1);
    }

    return ret;
}
