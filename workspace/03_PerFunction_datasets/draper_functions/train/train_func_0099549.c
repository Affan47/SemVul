put(struct child *c, const Str &key, const Str &val)
{
    always_assert(c->seq0_ == c->seq1_);

    unsigned int sseq = c->seq1_;
    c->conn->sendputwhole(key, val, sseq);
    c->conn->flush();

    const Json& result = c->conn->receive();
    always_assert(result && result[0] == sseq);

    ++c->seq0_;
    ++c->seq1_;
    ++c->nsent_;
    return 0;
}
