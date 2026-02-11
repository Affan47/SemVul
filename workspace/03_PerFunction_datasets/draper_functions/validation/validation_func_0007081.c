ShiftMultiVector(SmartPtr<MultiVectorMatrix>& V, const Vector& v_new)
  {
    Index ncols = V->NCols();

    SmartPtr<MultiVectorMatrix> new_V = V->MakeNewMultiVectorMatrix();

    for (Index i=0; i<ncols-1; i++) {
      new_V->SetVector(i, *V->GetVector(i+1));
    }
    new_V->SetVector(ncols-1, v_new);

    V = new_V;
  }
