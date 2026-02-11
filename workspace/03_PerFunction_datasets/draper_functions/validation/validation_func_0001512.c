inlineScan(InlineScanState *iss)
{
    condition = condition->inlineScan(iss);
    body = body ? body->inlineScan(iss) : NULL;
    return this;
}
