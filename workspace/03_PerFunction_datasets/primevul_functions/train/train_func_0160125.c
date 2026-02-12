static void show_regs_if_on_stack(struct stack_info *info, struct pt_regs *regs,
				  bool partial)
{


	if (!partial && on_stack(info, regs, sizeof(*regs))) {
		__show_regs(regs, 0);

	} else if (partial && on_stack(info, (void *)regs + IRET_FRAME_OFFSET,
				       IRET_FRAME_SIZE)) {


		show_iret_regs(regs);
	}
}
