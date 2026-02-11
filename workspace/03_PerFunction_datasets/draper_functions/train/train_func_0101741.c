ompfbe_mpi_task_write_pg_comm_module(fsbe_context *cx)
{
    int total_pe;
    Hmdf_table *p;
    Pe_in_pg *pe_in_pg;

    p = ompfbe_mpi_task_search_inner_hmdf_for_module(module_head);
    total_pe = p->pe_num * p->pc_num * p->clustering_num;

    ompfbe_iprintf(cx, "SUBROUTINE OSCAR_MPI_GEN_PG_COMM\n");
    fsbe_printf(cx, "C --- create pg communicator ---\n");

    pe_in_pg = mpi_task_get_pg_comm_list();

    mpi_task_write_pg_comm_module_var_decl(cx, total_pe);
    if( pe_in_pg != NULL){
	ompfbe_mpi_task_write_pg_comm_var(cx);
	mpi_task_write_pg_comm_save(cx);
    }

    mpi_task_write_get_rank_and_size(cx);
    mpi_task_write_check_process_num(cx, total_pe);
    if( pe_in_pg != NULL){
	mpi_task_write_get_comm_world_group(cx);
	mpi_task_write_gen_pg_comm(cx, total_pe);
    }

    ompfbe_iprintf(cx, "END\n\n");
}
