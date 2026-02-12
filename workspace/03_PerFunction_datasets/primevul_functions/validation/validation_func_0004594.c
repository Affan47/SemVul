void Compute(OpKernelContext* ctx) final {

    const CSRSparseMatrix* input_matrix;
    OP_REQUIRES_OK(ctx, ExtractVariantFromInput(ctx, 0, &input_matrix));
    const Tensor& input_permutation_indices = ctx->input(1);

    int64 num_rows;
    int batch_size;
    OP_REQUIRES_OK(ctx, ValidateInputs(*input_matrix, input_permutation_indices,
                                       &batch_size, &num_rows));


    Tensor batch_ptr(cpu_allocator(), DT_INT32, TensorShape({batch_size + 1}));
    auto batch_ptr_vec = batch_ptr.vec<int32>();
    batch_ptr_vec(0) = 0;


    std::vector<SparseMatrix> sparse_cholesky_factors(batch_size);


    const double nnz_per_row =
        (input_matrix->total_nnz() / batch_size) / num_rows;
    const int64 sparse_cholesky_cost_per_batch =
        nnz_per_row * nnz_per_row * num_rows;

    auto worker_threads = *(ctx->device()->tensorflow_cpu_worker_threads());
    std::atomic<int64> invalid_input_index(-1);
    Shard(worker_threads.num_threads, worker_threads.workers, batch_size,
          sparse_cholesky_cost_per_batch,
          [&](int64 batch_begin, int64 batch_end) {
            for (int64 batch_index = batch_begin; batch_index < batch_end;
                 ++batch_index) {


              Eigen::Map<const SparseMatrix> sparse_matrix(
                  num_rows, num_rows, input_matrix->nnz(batch_index),
                  input_matrix->row_pointers_vec(batch_index).data(),
                  input_matrix->col_indices_vec(batch_index).data(),
                  input_matrix->values_vec<T>(batch_index).data());

              Eigen::SimplicialLLT<SparseMatrix, Eigen::Upper,
                                   Eigen::NaturalOrdering<int>>
                  solver;
              auto permutation_indices_flat =
                  input_permutation_indices.flat<int32>().data();


              Eigen::Map<
                  Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic, int>>
                  permutation(permutation_indices_flat + batch_index * num_rows,
                              num_rows);
              auto permutation_inverse = permutation.inverse();

              SparseMatrix permuted_sparse_matrix;
              permuted_sparse_matrix.template selfadjointView<Eigen::Upper>() =
                  sparse_matrix.template selfadjointView<Eigen::Upper>()
                      .twistedBy(permutation_inverse);


              solver.compute(permuted_sparse_matrix);
              if (solver.info() != Eigen::Success) {
                invalid_input_index = batch_index;
                return;
              }


              sparse_cholesky_factors[batch_index] =
                  std::move(solver.matrixU());


              batch_ptr_vec(batch_index + 1) =
                  sparse_cholesky_factors[batch_index].nonZeros();
            }
          });


    OP_REQUIRES(
        ctx, invalid_input_index == -1,
        errors::InvalidArgument(
            "Sparse Cholesky factorization failed for batch index ",
            invalid_input_index.load(), ". The input might not be valid."));


    std::partial_sum(batch_ptr_vec.data(),
                     batch_ptr_vec.data() + batch_size + 1,
                     batch_ptr_vec.data());


    const int64 total_nnz = batch_ptr_vec(batch_size);
    Tensor output_row_ptr(cpu_allocator(), DT_INT32,
                          TensorShape({(num_rows + 1) * batch_size}));
    Tensor output_col_ind(cpu_allocator(), DT_INT32, TensorShape({total_nnz}));
    Tensor output_values(cpu_allocator(), DataTypeToEnum<T>::value,
                         TensorShape({total_nnz}));
    auto output_row_ptr_ptr = output_row_ptr.flat<int32>().data();
    auto output_col_ind_ptr = output_col_ind.flat<int32>().data();
    auto output_values_ptr = output_values.flat<T>().data();


    Shard(worker_threads.num_threads, worker_threads.workers, batch_size,
          (3 * total_nnz) / batch_size ,
          [&](int64 batch_begin, int64 batch_end) {
            for (int64 batch_index = batch_begin; batch_index < batch_end;
                 ++batch_index) {
              const SparseMatrix& cholesky_factor =
                  sparse_cholesky_factors[batch_index];
              const int64 nnz = cholesky_factor.nonZeros();

              std::copy(cholesky_factor.outerIndexPtr(),
                        cholesky_factor.outerIndexPtr() + num_rows + 1,
                        output_row_ptr_ptr + batch_index * (num_rows + 1));
              std::copy(cholesky_factor.innerIndexPtr(),
                        cholesky_factor.innerIndexPtr() + nnz,
                        output_col_ind_ptr + batch_ptr_vec(batch_index));
              std::copy(cholesky_factor.valuePtr(),
                        cholesky_factor.valuePtr() + nnz,
                        output_values_ptr + batch_ptr_vec(batch_index));
            }
          });


    CSRSparseMatrix output_csr_matrix;
    OP_REQUIRES_OK(
        ctx,
        CSRSparseMatrix::CreateCSRSparseMatrix(
            DataTypeToEnum<T>::value, input_matrix->dense_shape(), batch_ptr,
            output_row_ptr, output_col_ind, output_values, &output_csr_matrix));
    Tensor* output_csr_matrix_tensor;
    AllocatorAttributes cpu_alloc;
    cpu_alloc.set_on_host(true);
    OP_REQUIRES_OK(
        ctx, ctx->allocate_output(0, TensorShape({}), &output_csr_matrix_tensor,
                                  cpu_alloc));
    output_csr_matrix_tensor->scalar<Variant>()() =
        std::move(output_csr_matrix);
  }
