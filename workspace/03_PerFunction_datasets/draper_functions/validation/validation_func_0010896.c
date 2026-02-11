ReleasePolygons(Ring **polys, int npolys)
{
	int pi;

	for(pi=0; pi<npolys; pi++)
	{
		Ring *Poly, *temp;
		Poly = polys[pi];
		while(Poly != NULL){
			temp = Poly;
			Poly = Poly->next;
			free(temp->list);
			free(temp);
		}
	}
	free(polys);
}
