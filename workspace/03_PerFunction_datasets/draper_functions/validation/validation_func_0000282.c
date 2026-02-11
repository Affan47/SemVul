GetValueAsDouble( int iRow, int iField ) const

{
    if( iField < 0 || iField >= (int) aoFields.size() )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "iField (%d) out of range.", iField );

        return 0;
    }

    if( iRow < 0 || iRow >= nRowCount )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "iRow (%d) out of range.", iRow );

        return 0;
    }

    switch( aoFields[iField].eType )
    {
      case GFT_Integer:
        return aoFields[iField].anValues[iRow];

      case GFT_Real:
        return aoFields[iField].adfValues[iRow];

      case GFT_String:
        return atof( aoFields[iField].aosValues[iRow].c_str() );
    }

    return 0;
}
