_XNeighbors(Field f, xfieldT* xf, enum xr required)
{
    int n;

    ENTRY(("_XNeighbors(0x%x, 0x%x, %d)", f, xf, required));

    if (xf->neighbors_array) {
      EXIT(("OK: xf->neighbors_array != NULL"));
      return OK;
    }


    if (DXQueryGridConnections(xf->connections_array, &n, xf->k)) {
      if( xf->connectionType==ct_cubes && n != 3) {
	DXSetError(ERROR_DATA_INVALID,
		   "#13155","cubes",3);
	goto error;
      } else if( xf->connectionType==ct_quads && n != 2) {
	DXSetError(ERROR_DATA_INVALID,
		   "#13155","quads",2);
	goto error;
      } else if( xf->connectionType==ct_lines && n != 1) {
	DXSetError(ERROR_DATA_INVALID,
		   "#13155","lines",1);
	goto error;
      }
      EXIT(("OK"));
      return OK;
    } else {
      xf->neighbors_array = (Array) DXGetComponentValue(f, NEIGHBORS);
      if(!xf->neighbors_array) {
	xf->neighbors_array = DXNeighbors(f);
	if (!xf->neighbors_array) {
	  if (required) {
	    DXSetError(ERROR_MISSING_DATA, "#10240", NEIGHBORS);
	    EXIT(("ERROR"));
	    return ERROR;
	  } else {
	    EXIT(("OK"));
	    return OK;
	  }
	}
      }
      DXReference((dxObject)xf->neighbors_array);
      check(neighbors, "neighbors", TYPE_INT,
	    DXGetItemSize((Array)xf->connections_array)/DXTypeSize(TYPE_INT));
      compare(neighbors, "neighbors", xf->nconnections);
    }

    EXIT(("OK"));
    return OK;

  error:

    EXIT(("ERROR"));
    return ERROR;
}
