SetStatementPosition(Statement* stmt) {
  if (FLAG_debug_info) {
    CodeGenerator::RecordPositions(masm_, stmt->statement_pos());
  }
}
