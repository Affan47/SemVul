QuantizeCoordinatesLike(vtkSurface *Mesh)
{
	int i;
	double p[3];
	Mesh->GetScalingFactors(this->Factor,this->Tx,this->Ty,this->Tz);
	for (i=0;i<this->GetNumberOfPoints();i++)
	{
		this->Points->GetPoint(i,p);
		p[0] = floor( (p[0]-Tx) * Factor + 0.5 );
		p[1] = floor( (p[1]-Ty) * Factor + 0.5 );
		p[2] = floor( (p[2]-Tz) * Factor + 0.5 );
		this->Points->SetPoint(i,p);
	}
}
