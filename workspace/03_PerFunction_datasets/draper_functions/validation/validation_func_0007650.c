MakeLPRectFilter( const float bw, const int bits )
{
    const int tl = 8;
    const float pi = 3.1415926535;

    OneDArray<double> double_filter( Range( -tl, tl ) );
    OneDArray<int> int_filter( Range( -tl, tl) );


    for (int i=double_filter.First(); i<=double_filter.Last(); ++i)
    {
        double_filter[i] = cos( (pi*i)/
                                   (double_filter.Length()+1) );
    }


    for (int i=double_filter.First(); i<=double_filter.Last(); ++i)
    {
        double_filter[i] *= sinxoverx( pi*1.0*bw*i );
    }


    double sum = 0.0;
    for (int i=double_filter.First(); i<=double_filter.Last(); ++i)
        sum += double_filter[i];

    for (int i=double_filter.First(); i<=double_filter.Last(); ++i)
    {
        double_filter[i] *= double(1<<(bits+4));
        double_filter[i] /= sum;
    }


    for (int i=double_filter.First(); i<=double_filter.Last(); ++i)
    {
        int_filter[i] = double_filter[i]>0 ? int( double_filter[i]+0.5 ) : -int( -double_filter[i]+0.5 );
        int_filter[i] = (int_filter[i]+8)>>4;
    }

    return int_filter;
}
