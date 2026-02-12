static void add_interrupt_bench(cycles_t start)
{
        long delta = random_get_entropy() - start;


        delta = delta - ((avg_cycles + FIXED_1_2) >> AVG_SHIFT);
        avg_cycles += delta;

        delta = abs(delta) - ((avg_deviation + FIXED_1_2) >> AVG_SHIFT);
        avg_deviation += delta;
}
