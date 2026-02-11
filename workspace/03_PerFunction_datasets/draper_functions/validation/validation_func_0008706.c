bw_sum_of_squared_weights(Weight *self)
{
    BooleanQuery *bq = BQ(self->query);
    float sum = 0.0;
    int i;

    for (i = 0; i < BW(self)->w_cnt; i++) {
        if (! bq->clauses[i]->is_prohibited) {
            Weight *weight = BW(self)->weights[i];

            sum += weight->sum_of_squared_weights(weight);
        }
    }


    sum *= self->value * self->value;
    return sum;
}
