PrepareTriMesh( )
{
	if ( triMesh )
	{
		DestroyTriMesh( );
	}

	triMesh = new Mesh( *BMesh );
	triMesh->totface = 0;
	triMesh->mface.clear( );
}
