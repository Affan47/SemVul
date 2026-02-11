save( const string& fname) const
{
        ofstream of (fname, ios_base::trunc);
        if ( not of.good() )
                return CHypnogram::TError::nofile;

        of << _pagesize << endl;
        for ( size_t p = 0; p < _pages.size(); ++p )
                of << operator[](p).NREM << '\t' << operator[](p).REM << '\t' << operator[](p).Wake << endl;

        return CHypnogram::TError::ok;
}
