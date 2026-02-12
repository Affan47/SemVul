void XmpParser::unregisterNs(const std::string& )
    {
#ifdef EXV_HAVE_XMP_TOOLKIT
        try {


        }
        catch (const XMP_Error& e) {
            throw Error(kerXMPToolkitError, e.GetID(), e.GetErrMsg());
        }
#endif
    }
