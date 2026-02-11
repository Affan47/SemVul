Dump( FILE * fp )

{
    int    i;

    fprintf( fp, "SDTSRawLine\n" );
    fprintf( fp, "  Module=%s, Record#=%ld\n",
             oModId.szModule, oModId.nRecord );
    if( oLeftPoly.nRecord != -1 )
        fprintf( fp, "  LeftPoly (Module=%s, Record=%ld)\n",
                 oLeftPoly.szModule, oLeftPoly.nRecord );
    if( oRightPoly.nRecord != -1 )
        fprintf( fp, "  RightPoly (Module=%s, Record=%ld)\n",
                 oRightPoly.szModule, oRightPoly.nRecord );
    if( oStartNode.nRecord != -1 )
        fprintf( fp, "  StartNode (Module=%s, Record=%ld)\n",
                 oStartNode.szModule, oStartNode.nRecord );
    if( oEndNode.nRecord != -1 )
        fprintf( fp, "  EndNode (Module=%s, Record=%ld)\n",
                 oEndNode.szModule, oEndNode.nRecord );
    for( i = 0; i < nAttributes; i++ )
        fprintf( fp, "  Attribute (Module=%s, Record=%ld)\n",
                 paoATID[i].szModule, paoATID[i].nRecord );

    for( i = 0; i < nVertices; i++ )
    {
        fprintf( fp, "  Vertex[%3d] = (%.2f,%.2f,%.2f)\n",
                 i, padfX[i], padfY[i], padfZ[i] );
    }
}
