QPDFWriter::pushMD5Pipeline()
{
    if (! this->id2.empty())
    {

        throw std::logic_error(
            "Deterministic ID computation enabled after ID"
            " generation has already occurred.");
    }
    assert(this->deterministic_id);
    assert(this->md5_pipeline == 0);
    assert(this->pipeline->getCount() == 0);
    this->md5_pipeline = new Pl_MD5("qpdf md5", this->pipeline);
    this->md5_pipeline->persistAcrossFinish(true);


    pushPipeline(this->md5_pipeline);
    activatePipelineStack();
}
