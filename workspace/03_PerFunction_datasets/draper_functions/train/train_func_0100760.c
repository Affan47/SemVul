readMeshNodes(int data_set)
{
	Rc rc;
	int nd_id;
  static Point3 point;

	readFileLine(infile, read_buffer);


  int internal_id = 0;
	while (! endofDataset(read_buffer)) {


    nd_id = atol(read_buffer);


		readFileLine(infile, read_buffer);
    readPoint(read_buffer, point);

 		rc = model->addMeshNode(internal_id, nd_id, point);
    internal_id++;

    theControlCenter->update(internal_id, GUI_UPDATE_INTERVAL);

		if (rc != ECIF_OK)
			return rc;
		readFileLine(infile, read_buffer);
	}

	return ECIF_OK;
}
