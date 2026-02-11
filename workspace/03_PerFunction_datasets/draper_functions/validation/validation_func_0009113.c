from_tk_ReadBoundariesData(ClientData clientData, Tcl_Interp *interp,
          int argc, char* argv[])
{
  Model* model = theControlCenter->getModel();

  if (model == NULL) {
    TheUI->errMsg(0, "ReadBoundariesData: Command not legal. No model exists!");
    return TCL_OK;
  }

  model->setFlagValue(GEOMETRY_EDITED, GEOMETRY_EDITED_BOUNDARIES, true);

  if ( !model->getFlagValue(GEOMETRY_TYPE_CAD) ) {
    model->updateBoundaries();
    return TCL_OK;
  }


  int cnt = 0;
  linDeltaType* types = NULL;
  double* valuesU = NULL;
  int* useFixed = NULL;
  bool* useFixedN = NULL;

  int nof_vals;
  int nof_fns;

  char* type_str = NULL;

  int index = 0;
  while (true) {
    BodyElement* be = model->getBoundary(index++);
    if (be==NULL) break;
    int id = be->Id();

    readIdVariable(interp, "ObjectTable", id, "nofCmp", cnt);
    readIdVariable(interp, "ObjectTable", id, "dscTp", type_str);
    readIdVariable(interp, "ObjectTable", id, "dscU", nof_vals, valuesU);
    readIdVariable(interp, "ObjectTable", id, "useFN", nof_fns, useFixed);

    int nof_types = 0;

    if ( type_str != NULL ) {
      nof_types = strlen(type_str);
    }


    if ( nof_types > 0 ) {
      types = new linDeltaType[nof_types];

       for (int i = 0; i < nof_types; i++) {
        if ( type_str[i] == 'H' ) {
          types[i] = LIN_DELTA_H;
        } else if ( type_str[i] == 'N' ) {
          types[i] = LIN_DELTA_N;
        } else if ( type_str[i] == 'U' ) {
          types[i] = LIN_DELTA_U;
        } else {
          types[i] = LIN_DELTA_NONE;
        }
      }
    }


    if ( (nof_vals == 0  || nof_vals == cnt) &&
         (nof_types == 0 || nof_types == cnt) &&
          nof_fns == cnt
       ) {

      useFixedN = new bool[nof_fns];

      for (int i = 0; i < nof_fns; i++) {
        useFixedN[i] = (bool)useFixed[i];
      }

      be->setDiscretizationData(cnt, types, valuesU, NULL, useFixedN);
    }


    delete[] types; types = NULL;
    delete[] valuesU; valuesU = NULL;
    delete[] useFixedN; useFixedN = NULL;

    delete[] type_str; type_str = NULL;
    delete[] useFixed; useFixed = NULL;
  }

  model->updateCadGeometry();

  return TCL_OK;
}
