R_API RBinJavaStackMapFrame *r_bin_java_stack_map_frame_new(ut8 *buffer, ut64 sz, RBinJavaStackMapFrame *p_frame, ut64 buf_offset) {
	RBinJavaStackMapFrame *stack_frame = r_bin_java_default_stack_frame ();
	RBinJavaVerificationObj *se = NULL;
	ut64 offset = 0;
	if (!stack_frame) {
		return NULL;
	}
	stack_frame->tag = buffer[offset];
	offset += 1;
	stack_frame->metas->type_info = (void *) r_bin_java_determine_stack_frame_type (stack_frame->tag);
	stack_frame->type = ((RBinJavaStackMapFrameMetas *) stack_frame->metas->type_info)->type;
	stack_frame->file_offset = buf_offset;
	stack_frame->p_stack_frame = p_frame;
	switch (stack_frame->type) {
	case R_BIN_JAVA_STACK_FRAME_SAME:


		if (p_frame) {
			stack_frame->number_of_locals = p_frame->number_of_locals;
		} else {
			IFINT eprintf("><?><\n");
			IFDBG eprintf("Unable to set previous stackframe with the number of locals (current info.code_attr.implicit_frame was probably not set :/)");
		}
		IFDBG eprintf("r_bin_java_stack_map_frame_new: TODO Stack Frame Same Locals Condition is untested, so there may be issues.\n");
		break;
	case R_BIN_JAVA_STACK_FRAME_SAME_LOCALS_1:

		stack_frame->number_of_stack_items = 1;
		if (offset > sz) {
			r_bin_java_stack_frame_free (stack_frame);
			return NULL;
		}
		se = r_bin_java_read_from_buffer_verification_info_new (buffer + offset, sz - offset, buf_offset + offset);
		IFDBG eprintf("r_bin_java_stack_map_frame_new: Parsed R_BIN_JAVA_STACK_FRAME_SAME_LOCALS_1.\n");
		if (se) {
			offset += se->size;
		} else {
			eprintf ("r_bin_java_stack_map_frame_new: Unable to parse the Stack Items for the stack frame.\n");
			r_bin_java_stack_frame_free (stack_frame);
			return NULL;
		}
		r_list_append (stack_frame->stack_items, (void *) se);


		if (p_frame) {
			stack_frame->number_of_locals = p_frame->number_of_locals;
		} else {
			IFDBG eprintf("Unable to set previous stackframe with the number of locals (current info.code_attr.implicit_frame was probably not set :/)");
		}
		IFDBG eprintf("r_bin_java_stack_map_frame_new: TODO Stack Frame Same Locals 1 Stack Element Condition is untested, so there may be issues.\n");
		break;
	case R_BIN_JAVA_STACK_FRAME_CHOP:


		IFDBG eprintf("r_bin_java_stack_map_frame_new: Parsing R_BIN_JAVA_STACK_FRAME_CHOP.\n");


		stack_frame->offset_delta = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;


		if (p_frame) {
			stack_frame->number_of_locals = p_frame->number_of_locals;
		} else {
			IFINT eprintf("><?><\n");
			IFDBG eprintf("Unable to set previous stackframe with the number of locals (current info.code_attr.implicit_frame was probably not set :/)");
		}
		IFDBG eprintf("r_bin_java_stack_map_frame_new: TODO Stack Frame Chop Condition is untested, so there may be issues.\n");
		break;
	case R_BIN_JAVA_STACK_FRAME_SAME_FRAME_EXTENDED:
		IFDBG eprintf("r_bin_java_stack_map_frame_new: Parsing R_BIN_JAVA_STACK_FRAME_SAME_FRAME_EXTENDED.\n");

		stack_frame->offset_delta = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;

		stack_frame->number_of_stack_items = 1;
		se = r_bin_java_read_from_buffer_verification_info_new (buffer + offset, sz - offset, buf_offset + offset);
		if (se) {
			offset += se->size;
		} else {
			eprintf ("r_bin_java_stack_map_frame_new: Unable to parse the Stack Items for the stack frame.\n");
			r_bin_java_stack_frame_free (stack_frame);
			return NULL;
		}
		r_list_append (stack_frame->stack_items, (void *) se);


		if (p_frame) {
			stack_frame->number_of_locals = p_frame->number_of_locals;
		} else {
			IFINT eprintf("><?><\n");
			IFDBG eprintf("Unable to set previous stackframe with the number of locals (current info.code_attr.implicit_frame was probably not set :/)");
		}
		IFDBG eprintf("r_bin_java_stack_map_frame_new: TODO Stack Frame Same Locals Frame Stack 1 Extended Condition is untested, so there may be issues.\n");
		break;
	case R_BIN_JAVA_STACK_FRAME_APPEND:
		IFDBG eprintf("r_bin_java_stack_map_frame_new: Parsing R_BIN_JAVA_STACK_FRAME_APPEND.\n");


		ut16 k = stack_frame->tag - 251;
		ut32 i = 0;

		stack_frame->offset_delta = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;


		for (i = 0; i < k; i++) {
			if (offset >= sz) {
				break;
			}
			IFDBG eprintf("r_bin_java_stack_map_frame_new: Parsing verifying the k'th frame: %d of %d.\n", i, k);
			se = r_bin_java_read_from_buffer_verification_info_new (buffer + offset, sz - offset, buf_offset + offset);
			IFDBG eprintf("r_bin_java_stack_map_frame_new: Completed Parsing\n");
			if (se) {
				offset += se->size;
			} else {
				eprintf ("r_bin_java_stack_map_frame_new: Unable to parse the locals for the stack frame.\n");
				r_bin_java_stack_frame_free (stack_frame);
				return NULL;
			}
			r_list_append (stack_frame->local_items, (void *) se);
		}
		IFDBG eprintf("r_bin_java_stack_map_frame_new: Breaking out of loop");
		IFDBG eprintf("p_frame: %p\n", p_frame);
		if (p_frame) {
			stack_frame->number_of_locals = p_frame->number_of_locals + k;
		} else {
			IFINT eprintf("><?><\n");
			IFDBG eprintf("Unable to set previous stackframe with the number of locals (current info.code_attr.implicit_frame was probably not set :/)");
		}
		IFDBG eprintf("r_bin_java_stack_map_frame_new: TODO Stack Frame Same Locals Frame Stack 1 Extended Condition is untested, so there may be issues.\n");
		break;
	case R_BIN_JAVA_STACK_FRAME_FULL_FRAME:
		IFDBG eprintf("r_bin_java_stack_map_frame_new: Parsing R_BIN_JAVA_STACK_FRAME_FULL_FRAME.\n");
		stack_frame->offset_delta = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;


		stack_frame->number_of_locals = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;

		IFDBG r_bin_java_print_stack_map_frame_summary(stack_frame);

		for (i = 0; i < stack_frame->number_of_locals; i++) {
			if (offset >= sz) {
				break;
			}
			se = r_bin_java_read_from_buffer_verification_info_new (buffer + offset, sz - offset, buf_offset + offset);
			if (se) {
				offset += se->size;

			} else {
				eprintf ("r_bin_java_stack_map_frame_new: Unable to parse the locals for the stack frame.\n");
				r_bin_java_stack_frame_free (stack_frame);
				return NULL;
			}
			r_list_append (stack_frame->local_items, (void *) se);
		}

		stack_frame->number_of_stack_items = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;


		for (i = 0; i < stack_frame->number_of_stack_items; i++) {
			if (offset >= sz) {
				break;
			}
			se = r_bin_java_read_from_buffer_verification_info_new (buffer + offset, sz - offset, buf_offset + offset);
			if (se) {
				offset += se->size;

			} else {
				eprintf ("r_bin_java_stack_map_frame_new: Unable to parse the stack items for the stack frame.\n");
				r_bin_java_stack_frame_free (stack_frame);
				return NULL;
			}
			r_list_append (stack_frame->local_items, (void *) se);
		}
		break;
	default:
		eprintf ("java: Unknown type\n");
		break;
	}

	stack_frame->size = offset;

	return stack_frame;
}
