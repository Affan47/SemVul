Tm3RotateBetween( Transform3 T, Point3 *vfrom, Point3 *vto )
{
	Point3 Vu;
	float len, sinA, cosA, versA;

	Tm3Identity( T );

	len = sqrt(Pt3Dot(vfrom,vfrom) * Pt3Dot(vto,vto));
	if(len == 0) return;

	cosA = Pt3Dot(vfrom,vto) / len;
	versA = 1 - cosA;

	Pt3Cross( vfrom, vto, &Vu );
	sinA = Pt3Length( &Vu ) / len;
	if(sinA == 0) return;

	Pt3Mul( 1/(len*sinA), &Vu, &Vu );

	T[TMX][TMX] = Vu.x*Vu.x*versA + cosA;
	T[TMY][TMX] = Vu.x*Vu.y*versA - Vu.z*sinA;
	T[TMZ][TMX] = Vu.x*Vu.z*versA + Vu.y*sinA;

	T[TMX][TMY] = Vu.y*Vu.x*versA + Vu.z*sinA;
	T[TMY][TMY] = Vu.y*Vu.y*versA + cosA;
	T[TMZ][TMY] = Vu.y*Vu.z*versA - Vu.x*sinA;

	T[TMX][TMZ] = Vu.x*Vu.z*versA - Vu.y*sinA;
	T[TMY][TMZ] = Vu.y*Vu.z*versA + Vu.x*sinA;
	T[TMZ][TMZ] = Vu.z*Vu.z*versA + cosA;
}
