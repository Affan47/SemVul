static void Run(const Tensor& in_x, const Tensor& in_y, bool lower,
                  bool adjoint, const MatMulBCast& bcast, Tensor* out,
                  int start, int limit) {
    const bool should_bcast = bcast.IsBroadcastingRequired();
    const auto& x_batch_indices = bcast.x_batch_indices();
    const auto& y_batch_indices = bcast.y_batch_indices();
    int num_bands = in_x.dim_size(1);
    int matrix_size = in_x.dim_size(2);

    for (int64 i = start; i < limit; ++i) {
      const int64 x_batch_index = should_bcast ? x_batch_indices[i] : i;
      const int64 y_batch_index = should_bcast ? y_batch_indices[i] : i;
      auto matrix = ConstTensorSliceToEigenMatrix(in_x, x_batch_index);
      auto rhs = ConstTensorSliceToEigenMatrix(in_y, y_batch_index);
      auto output = TensorSliceToEigenMatrix(out, i);


      if (lower) {
        if (!adjoint) {
          output.row(0) = rhs.row(0) / matrix(0, 0);
          for (int i = 1; i < matrix_size; ++i) {
            if (i < num_bands) {
              output.row(i).noalias() =
                  (rhs.row(i) - matrix.block(1, i, i, 1).reverse().transpose() *
                                    output.topRows(i)) /
                  matrix(0, i);
            } else {
              output.row(i).noalias() =
                  (rhs.row(i) -
                   matrix.block(1, i, num_bands - 1, 1).reverse().transpose() *
                       output.middleRows(i - (num_bands - 1), num_bands - 1)) /
                  matrix(0, i);
            }
          }
        } else {


          output.row(matrix_size - 1) =
              rhs.row(matrix_size - 1) / eigen_conj(matrix(0, matrix_size - 1));
          for (int i = matrix_size - 1; i >= 0; --i) {
            output.row(i).noalias() = rhs.row(i);
            for (int j = i + 1; j < std::min(matrix_size, i + num_bands); ++j) {
              output.row(i).noalias() -=
                  eigen_conj(matrix(j - i, j)) * output.row(j);
            }
            output.row(i) /= eigen_conj(matrix(0, i));
          }
        }
      } else {
        if (!adjoint) {
          output.row(matrix_size - 1) =
              rhs.row(matrix_size - 1) / matrix(num_bands - 1, matrix_size - 1);
          for (int i = 1; i < matrix_size; ++i) {
            int k = matrix_size - 1 - i;
            if (i < num_bands) {
              output.row(k).noalias() =
                  (rhs.row(k) - matrix.block(num_bands - 1 - i, k, i, 1)
                                        .reverse()
                                        .transpose() *
                                    output.bottomRows(i)) /
                  matrix(num_bands - 1, k);
            } else {
              output.row(k).noalias() =
                  (rhs.row(k) -
                   matrix.block(0, k, num_bands - 1, 1).reverse().transpose() *
                       output.middleRows(k + 1, num_bands - 1)) /
                  matrix(num_bands - 1, k);
            }
          }
        } else {
          output.row(0) = rhs.row(0) / eigen_conj(matrix(num_bands - 1, 0));
          for (int i = 1; i < matrix_size; ++i) {
            output.row(i).noalias() = rhs.row(i);
            for (int j = std::max(0, i - (num_bands - 1)); j < i; ++j) {
              output.row(i).noalias() -=
                  eigen_conj(matrix(num_bands - 1 - (i - j), j)) *
                  output.row(j);
            }
            output.row(i) /= eigen_conj(matrix(num_bands - 1, i));
          }
        }
      }
    }
  }
