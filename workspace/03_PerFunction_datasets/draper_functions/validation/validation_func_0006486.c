move_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((register_operand (op, mode)) || ((memory_operand (op, mode)) && (
#line 139 "/home/dcharvest/ubuntu64-builder/genericMake/build/toolchain/dl/gcc-4.7.4/gcc/config/xtensa/predicates.md"
(!constantpool_mem_p (op)
			    || GET_MODE_SIZE (mode) % UNITS_PER_WORD == 0)))) || (((GET_CODE (op) == CONST_INT) && (
#line 142 "/home/dcharvest/ubuntu64-builder/genericMake/build/toolchain/dl/gcc-4.7.4/gcc/config/xtensa/predicates.md"
(GET_MODE_CLASS (mode) == MODE_INT
			    && xtensa_simm12b (INTVAL (op))))) || ((GET_CODE (op) == CONST_INT || GET_CODE (op) == CONST_DOUBLE || GET_CODE (op) == CONST || GET_CODE (op) == SYMBOL_REF || GET_CODE (op) == LABEL_REF) && (
#line 145 "/home/dcharvest/ubuntu64-builder/genericMake/build/toolchain/dl/gcc-4.7.4/gcc/config/xtensa/predicates.md"
(TARGET_CONST16 && CONSTANT_P (op)
			    && GET_MODE_SIZE (mode) % UNITS_PER_WORD == 0))));
}
