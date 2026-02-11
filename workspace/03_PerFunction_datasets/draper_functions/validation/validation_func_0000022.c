bios_putchar ( int character ) {
	int discard_a, discard_b, discard_c;


	character = ansiesc_process ( &bios_ansiesc_ctx, character );
	if ( character < 0 )
		return;


	__asm__ __volatile__ ( REAL_CODE ( "sti\n\t"

					   "cmpb $0x20, %%al\n\t"
					   "jb 1f\n\t"

					   "movw $0x0001, %%cx\n\t"
					   "movb $0x09, %%ah\n\t"
					   "int $0x10\n\t"
					   "\n1:\n\t"

					   "xorw %%bx, %%bx\n\t"
					   "movb $0x0e, %%ah\n\t"
					   "int $0x10\n\t"
					   "cli\n\t" )
			       : "=a" ( discard_a ), "=b" ( discard_b ),
			         "=c" ( discard_c )
			       : "a" ( character ), "b" ( bios_attr )
			       : "ebp" );
}
