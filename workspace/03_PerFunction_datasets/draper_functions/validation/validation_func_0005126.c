cbRead(wxFile& file, wxString& st, wxFontEncoding encoding)
{
    st.Empty();
    if (!file.IsOpened())
        return false;

    int len = file.Length();
    if (!len)
    {
        file.Close();
        return true;
    }

    char* buff = new char[len+1];
    if (!buff)
    {
        file.Close();
        return false;
    }
    file.Read((void*)buff, len);
    file.Close();
    buff[len]='\0';

    DetectEncodingAndConvert(buff, st, encoding);
    delete [] buff;

    return true;
}
