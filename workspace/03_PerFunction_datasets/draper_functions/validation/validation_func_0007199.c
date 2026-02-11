JacobianInverse(const VectorType & pt, MatrixType & invJ, const MatrixType *pJ) const
{
  MatrixType *pJlocal = ITK_NULLPTR;


  if( pJ == ITK_NULLPTR )
    {
    pJlocal = new MatrixType();
    this->Jacobian(pt, *pJlocal);
    pJ = pJlocal;
    }


  invJ.set_size(2, 3);

  Float idet = 1.0 / this->JacobianDeterminant(pt, pJ);

  invJ[0][0] = idet * ( ( *pJ )[1][1] - ( *pJ )[2][1] ); invJ[0][1] = idet * ( ( *pJ )[2][1] - ( *pJ )[0][1] );
  invJ[0][2] = idet * ( ( *pJ )[0][1] - ( *pJ )[1][1] );
  invJ[1][0] = idet * ( ( *pJ )[2][0] - ( *pJ )[1][0] ); invJ[1][1] = idet * ( ( *pJ )[0][0] - ( *pJ )[2][0] );
  invJ[1][2] = idet * ( ( *pJ )[1][0] - ( *pJ )[0][0] );

  delete pJlocal;
}
