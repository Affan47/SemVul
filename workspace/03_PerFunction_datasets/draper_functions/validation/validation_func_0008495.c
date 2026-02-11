calcDistX(float* afDistX, int iStart, int iFinish, t_Flows *ptFlows, t_Unique *ptUnique)
{
    int i = 0, j = 0, nN = ptFlows->nN, nU = ptUnique->nU, nM = ptUnique->nM;
    short* asU = ptUnique->asU;
    short* asData = ptFlows->asData;
    int*   anLengths = ptFlows->anLengths;

    for(i = iStart; i < iFinish; i++){
	for(j = 0; j < nU; j++){
      		afDistX[i*nU + j] = alignX(&asU[j*nM], &asData[i*nM], ptUnique->anLenU[j], anLengths[i]);;
	}
    }
}
