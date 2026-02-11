automaton_step(sosemanuk_state *state)
{
  uint32_t *r = state->r;
  uint32_t *s = state->s;
  uint32_t r0_prev = r[0];
  uint8_t t = state->t;

  r[0] = r[1] + ((r0_prev & 1u) ? s[(t+1)%10] ^ s[(t+8)%10] : s[(t+1)%10]);
  r[1] = rotl(r0_prev * 0x54655307, 7);

  return (s[(t+9)%10] + r[0]) ^ r[1];
}
