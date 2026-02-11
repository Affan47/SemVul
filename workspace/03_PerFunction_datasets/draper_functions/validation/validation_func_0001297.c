GetNoDataValue( int *pbSuccess )

{
    if( pbSuccess )
        *pbSuccess = bNoDataSet;

    if( bNoDataSet )
        return dfNoData;
    else
        return 0.0;
}
