cc_register (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == REG) && ((
#line 303 "../../src/gcc/config/arm/predicates.md"
(REGNO (op) == CC_REGNUM)) && ((
#line 304 "../../src/gcc/config/arm/predicates.md"
(mode == GET_MODE (op))) || (
#line 305 "../../src/gcc/config/arm/predicates.md"
(mode == VOIDmode && GET_MODE_CLASS (GET_MODE (op)) == MODE_CC))));
}
