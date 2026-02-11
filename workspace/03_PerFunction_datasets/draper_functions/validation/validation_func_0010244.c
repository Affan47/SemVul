to_tk_WriteAllParamDataPre(Tcl_Interp* interp, const Model& model)
{
  int nof_params = 20;
  int nof_pstrms =  3;

  int ids_buffer[10000];


  ecif_parameterType param_types[] = {
    ECIF_BODY_FORCE,
    ECIF_BODY_PARAMETER,
    ECIF_BOUNDARY_CONDITION,
    ECIF_BOUNDARY_PARAMETER,
    ECIF_CALCULATOR,
    ECIF_CONSTANT,
    ECIF_COORDINATE,
    ECIF_DATAFILE,
    ECIF_EQUATION,
    ECIF_EQUATION_VARIABLE,
    ECIF_GRID_H,
    ECIF_GRID_PARAMETER,
    ECIF_INITIAL_CONDITION,
    ECIF_MATERIAL,
    ECIF_MODEL_PARAMETER,
    ECIF_SIMULATION_PARAMETER,
    ECIF_SOLVER,
    ECIF_SOLVER_CONTROL,
    ECIF_TIMESTEP,
    ECIF_USER_SETTING
  };

  char* param_arries[] = {
    "BodyForce",
    "BodyParameter",
    "BoundaryCondition",
    "BoundaryParameter",
    "Calculator",
    "Constant",
    "Coordinate",
    "Datafile",
    "Equation",
    "EquationVariable",
    "GridH",
    "GridParameter",
    "InitialCondition",
    "Material",
    "ModelParameter",
    "SimulationParameter",
    "Solver",
    "SolverControl",
    "Timestep",
    "UserSetting"
  };


  Model* mdl = (Model*) &model;

  for (int i = 0; i < nof_params; i++) {


    writeVariable(interp, param_arries[i], "ids", 0, (int*)NULL);
    writeVariable(interp, param_arries[i], "nextNewParameterId", mdl->getNextNewParameterId(param_types[i]));

    int index = 0;
    while (true) {
      Parameter* param = mdl->getParameter(index++, param_types[i]);
      if (param==NULL) break;
      int pid = param->ID();
      ids_buffer[index - 1] = pid;
      writeIdVariable(interp, param_arries[i], pid, "data", (char*)param->getValue());
      writeIdVariable(interp, param_arries[i], pid, "name", (char*)param->getName());
      writeIdVariable(interp, param_arries[i], pid, "oid", param->getParentId());
    }

    if (index > 1 ) {
      writeVariable(interp, param_arries[i], "ids", index-1, ids_buffer);
    }

  }


  sendCommandToGui(interp, "Interface::applyAllParameterDataPre");
}
