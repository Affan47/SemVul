sem_unlock(int sem_set_id) {
struct sembuf sem_op;


	sem_op.sem_num = 0;
	sem_op.sem_op  = 1;
	sem_op.sem_flg = 0;
	if ( semop(sem_set_id, &sem_op, 1) == 0 )
		return;

	LogError("semop() error in %s line %d: %s", __FILE__, __LINE__, strerror(errno) );

}
