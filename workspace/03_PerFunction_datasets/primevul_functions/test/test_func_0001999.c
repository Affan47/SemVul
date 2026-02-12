Status GraphProperties::UpdateShapes(
    SymbolicShapeRefiner* shape_refiner,
    const absl::flat_hash_map<const NodeDef*, const NodeDef*>& resource_handles,
    const NodeDef* n, bool* new_shapes) const {
  if (IsEnter(*n)) {


    TF_RETURN_IF_ERROR(UpdateEnter(shape_refiner, n, new_shapes));
  } else if (IsMerge(*n)) {

    TF_RETURN_IF_ERROR(UpdateMerge(shape_refiner, n, new_shapes));
  } else if (IsEnqueue(*n)) {


    TF_RETURN_IF_ERROR(
        UpdateEnqueue(n, resource_handles, shape_refiner, new_shapes));
  } else if (IsQueue(*n)) {

    TF_RETURN_IF_ERROR(UpdateQueue(n, shape_refiner, new_shapes));
  } else {


    TF_RETURN_IF_ERROR(shape_refiner->UpdateNode(n, new_shapes));
  }

  return Status::OK();
}
