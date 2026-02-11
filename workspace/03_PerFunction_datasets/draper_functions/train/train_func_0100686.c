figure_type_and_name( const string& h_)
{
        auto tt = agh::str::tokens( h_, "-");
        if ( tt.size() == 2 ) {
                for ( auto& T : _CT_ )
                        if ( all_of( tt.begin(), tt.end(),
                                     [&]( const string& t)
                                     {
                                             return any_of( T.second.begin(), T.second.end(),
                                                            [&]( const string& h)
                                                            {
                                                                    return 0 == strcasecmp( h.c_str(), t.c_str());
                                                            });
                                     }) )
                                return make_tuple(T.first, 0);
                return make_tuple(TType::other, 0);

        } else if ( tt.size() == 1 ) {
                for ( auto& T : _CT_ )
                        for ( size_t i = 0; i < T.second.size(); ++i )
                                if ( strcasecmp( T.second[i], h_.c_str()) == 0 ) {
                                        return make_tuple(T.first, (int)i);
                                }
        }

        return make_tuple(TType::other, 0);
}
