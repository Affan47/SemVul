squadTangent( const Quat4f& before, const Quat4f& center, const Quat4f& after )
{
	Quat4f l1 = Quat4f::logDifference( center, before );
	Quat4f l2 = Quat4f::logDifference( center, after );

	Quat4f e;
	for( int i = 0; i < 4; ++i )
	{
		e[ i ] = -0.25f * ( l1[ i ] + l2[ i ] );
	}
	e = center * ( e.exp() );

	return e;
}
