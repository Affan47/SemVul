const char* _exvGettext(const char* str)
{

    {
        std::lock_guard<std::mutex> lock(exvGettextInitializedMutex);

        if (!exvGettextInitialized) {

            const std::string localeDir = Exiv2::getProcessPath() + EXV_LOCALEDIR;
            bindtextdomain(EXV_PACKAGE_NAME, localeDir.c_str());
#ifdef EXV_HAVE_BIND_TEXTDOMAIN_CODESET
            bind_textdomain_codeset(EXV_PACKAGE_NAME, "UTF-8");
#endif
            exvGettextInitialized = true;
        }
    }
    return dgettext(EXV_PACKAGE_NAME, str);
}
