/* File: translate_binop.h */
/* Creation Date: 2017-01-28 */
/* Creator: Dmitry Guzeev <dmitry.guzeev@yahoo.com> */
/* Description: */
/* translate_binop_node() function */

#ifndef TRANSLATE_BINOP_H
#define TRANSLATE_BINOP_H

#include "core/compiler/ast/ast_node.h"
#include "core/compiler/translator/translator.h"
#include "lib/types.h"

bool translate_binop_node(struct Translator* T, struct ASTNode* node);

#endif /* TRANSLATE_BINOP_H */
