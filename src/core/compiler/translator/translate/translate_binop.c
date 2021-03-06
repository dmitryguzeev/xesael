/* File: translate_binop.c */
/* Creation Date: 2017-01-28 */
/* Creator: Dmitry Guzeev <dmitry.guzeev@yahoo.com> */
/* Description: */
/* translate_binop_node() function */

#include "translate_binop.h"

#include "core/compiler/ast/ast_node.h"
#include "core/compiler/translator/translate/translate.h"
#include "core/compiler/translator/translator.h"
#include "lib/types.h"

bool translate_binop_node(struct Translator* T, struct ASTNode* node)
{
  /* Assign the current free register ID to a node register ID */
  node->rid = translator_get_free_reg(T);

  /* Retreive and translate the left operand */
  struct ASTNode* lop = node->data.binop.lop;
  if (!translate_node(T, lop)) return false;

  /* Retreive and translate the right operand */
  struct ASTNode* rop = node->data.binop.rop;
  if (!translate_node(T, rop)) return false;

  /* Select the instruction code depending on the node type */
  enum InstructionOpCode code;
  code = binop_instr_code_from_ast_node(node);

  /* Emit the actual instruction */
  const Instruction instr =
    instr_binop_new(code, lop->rid, rop->rid, node->rid);
  translator_append_instr(T, instr);

  /* Succeed */
  return true;
}
