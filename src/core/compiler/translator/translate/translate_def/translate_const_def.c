/* File: translate_const_def.c */
/* Creation Date: 2017-01-30 */
/* Creator: Dmitry Guzeev <dmitry.guzeev@yahoo.com> */
/* Description: */
/* translate_const_def_node() function */

#include "core/compiler/translator/translate/translate_def/translate_const_def.h"

#include "core/compiler/ast/ast_node.h"
#include "core/compiler/compiler.h"
#include "core/compiler/translator/translate/translate.h"
#include "core/compiler/translator/translator.h"
#include "err.h"
#include "lib/types.h"

bool translate_const_def_node(struct Translator* T, struct ASTNode* node)
{
  /* Retreive and compile the initializator node */
  struct ASTNode* initializator;
  initializator = node->data.const_def.initializator;
  if (!translate_node(T, initializator)) return false;

  /* Retreive the constant name */
  struct Object* name_obj = node->data.const_def.name;
  char* name              = name_obj->data.str.val;

  /* Create a new immediate that will store the constant name */
  struct Immediate* name_immediate;
  name_immediate = translator_immediate_insert(T, name, name_obj);

  /* Create a new constant symbol and try to insert it */
  /* to the symbol table */
  struct Symbol* sym = sym_const_new(name, name_immediate->id);
  translator_st_insert(T, sym);

  /* If failed */
  if (!sym) {
    /* Set the appropriate error message */
    compiler_err_setf(
      node->ln, "constant with name \"%s\" is already defined", name);
    /* Fail */
    return false;
  }

  /* Emit a new VARSET instruction */
  Instruction instr = instr_varset_new(name_immediate->id, initializator->rid);
  translator_append_instr(T, instr);

  /* Succeed */
  return true;
}
