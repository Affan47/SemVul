visit( const KBookmark &bk ) {

    m_out << "#URL" << endl;
    m_out << "\tNAME=" << bk.fullText() << endl;
    m_out << "\tURL=" << bk.url().url().toUtf8() << endl;
    m_out << endl;
}
