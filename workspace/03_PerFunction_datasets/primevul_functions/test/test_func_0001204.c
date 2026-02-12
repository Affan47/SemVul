bool ConstantFolding::ConstantPushDownBiasAdd(GraphProperties* properties,
                                              GraphDef* optimized_graph,
                                              NodeDef* node) {


  const bool parent_is_bias_add = IsBiasAdd(*node);
  if (!parent_is_bias_add && !IsAdd(*node)) return false;
  ConstantPushDownContext ctx;
  if (!PrepareConstantPushDown(*node, *properties,
                               true, &ctx)) {
    return false;
  }


  if (ctx.left_child_is_const && parent_is_bias_add) return false;
  const bool child_is_bias_add = IsBiasAdd(*ctx.op_child);
  if (!child_is_bias_add && !IsAdd(*ctx.op_child)) return false;


  if (ctx.parent_input_props->empty() || ctx.op_child_input_props->empty() ||
      (*ctx.parent_input_props)[0].shape().unknown_rank() ||
      (*ctx.parent_input_props)[1].shape().unknown_rank() ||
      (*ctx.op_child_input_props)[0].shape().unknown_rank() ||
      (*ctx.op_child_input_props)[1].shape().unknown_rank()) {
    return false;
  }


  const int left_leaf_rank = (*ctx.op_child_input_props)[0].shape().dim_size();
  const int right_leaf_rank = (*ctx.op_child_input_props)[1].shape().dim_size();

  if (left_leaf_rank != 1 && right_leaf_rank != 1) return false;
  const int vector_idx = left_leaf_rank == 1 ? 0 : 1;
  const int matrix_idx = 1 - vector_idx;

  const auto& vector_prop = (*ctx.op_child_input_props)[vector_idx];
  const int vector_rank = vector_idx == 0 ? left_leaf_rank : right_leaf_rank;
  if (vector_rank != 1) return false;
  const DataType vector_type = vector_prop.dtype();

  const auto& matrix_prop = (*ctx.op_child_input_props)[matrix_idx];
  const int matrix_rank = matrix_prop.shape().dim_size();
  const DataType matrix_type = matrix_prop.dtype();

  const int const_idx = ctx.left_child_is_const ? 0 : 1;
  const auto& const_prop = (*ctx.parent_input_props)[const_idx];
  const int const_rank = const_prop.shape().dim_size();
  const DataType const_type = const_prop.dtype();

  int input_to_swap = -1;

  if (!parent_is_bias_add && child_is_bias_add && const_rank == matrix_rank &&
      const_type == matrix_type) {

    input_to_swap = matrix_idx;
  } else if (const_rank == 1 && const_type == vector_type) {

    input_to_swap = vector_idx;
  }
  if (input_to_swap == -1) return false;
  const NodeDef* leaf_to_swap =
      node_map_->GetNode(ctx.op_child->input(input_to_swap));
  if (IsConstant(*leaf_to_swap)) return false;

  node_map_->UpdateInput(node->name(), node->input(const_idx),
                         ctx.op_child->input(input_to_swap));
  node_map_->AddOutput(node->input(const_idx), ctx.op_child->name());
  if (ctx.op_child->input(input_to_swap) !=
      ctx.op_child->input(1 - input_to_swap)) {
    node_map_->RemoveOutput(ctx.op_child->input(input_to_swap),
                            ctx.op_child->name());
  }
  std::swap(*node->mutable_input(const_idx),
            *ctx.op_child->mutable_input(input_to_swap));
  properties->ClearInputProperties(node->name());
  properties->ClearInputProperties(ctx.op_child->name());

  return true;
}
