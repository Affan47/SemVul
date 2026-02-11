go(){
    struct queue_t *running_queue = get_process(RUNNING);
    struct queue_t *ready0_queue = get_process(READY0);
    struct process_control_block *run_me_next;
    int error;
    int i = 0;

    if (running_queue->head != null){

		if (scheduler == GROUP){
			error = move(RUNNING, running_queue->head->group);


			if (error == ERROR_QUEUE_EMPTY || error == ERROR_QUEUE_FULL){
				return error;
			}
			global_quantum_count++;
			if (global_quantum_count >= MAX_QUANTUM){
				error = switch_group();
				if (error == ERROR_SWITCH_DEFAULT){
					return error;
				}
			}
		}

		else if (scheduler == PRIORITY){

			run_me_next = iterate(1);


		    if(running_queue->head->priority > 1){
				running_queue->head->priority--;
			}
			error = move(RUNNING, READY0);


            if (run_me_next == null){
                run_me_next = ready0_queue->head;
            }


			if (error == ERROR_QUEUE_FULL || error == ERROR_QUEUE_EMPTY){
				return error;
			}
		}
    }

	else{

		if (scheduler == GROUP){
			global_quantum_count++;
			if (global_quantum_count >= MAX_QUANTUM){
				error = switch_group();
				if (error == ERROR_SWITCH_DEFAULT){
					return error;
				}
			}
		}

		else{
			run_me_next = iterate(1);

			if (run_me_next == null){
				return ERROR_NO_READY_PROCESS;
			}
		}
	}


	if (scheduler == GROUP){
		i = 0;

		while (i < 4){
			error = move(current_group, RUNNING);


			if (error == ERROR_QUEUE_EMPTY){

				if (i == 3){
					return ERROR_NO_READY_PROCESS;
				}
				switch_group();
			}

			else if (error == ERROR_QUEUE_FULL){
				return error;
			}

			else if (error == ERROR_SUCCESS){
				break;
			}
			i++;
		}
	}

	else{
		struct process_control_block temp = delete(READY0, run_me_next);

		if(temp.pid == ERROR_PROCESS_NOT_EXIST){
			return ERROR_PROCESS_NOT_EXIST;
		}

		else if(temp.pid == ERROR_QUEUE_EMPTY){
			return ERROR_QUEUE_EMPTY;
		}
		error = enqueue(RUNNING, temp.pid, temp.psw, temp.page_table, temp.regs, temp.priority, temp.quantum_count, temp.group);

		if (error == ERROR_QUEUE_FULL){
			return ERROR_QUEUE_FULL;
		}
	}

	return ERROR_SUCCESS;
}
