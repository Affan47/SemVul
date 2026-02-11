phsc_explain(Scorer *self, int doc_num)
{
    PhraseScorer *phsc = PhSc(self);
    float phrase_freq;

    phsc_skip_to(self, doc_num);

    phrase_freq = (self->doc == doc_num) ? phsc->freq : 0.0f;
    return expl_new(sim_tf(self->similarity, phrase_freq),
                    "tf(phrase_freq=%f)", phrase_freq);
}
