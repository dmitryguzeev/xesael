/* File: translate_lit.h */
/* Creation Date: 2017-01-28 */
/* Creator: Dmitry Guzeev <dmitry.guzeev@yahoo.com> */
/* Description: */
/* The translate_lit_node() function */

#ifndef TRANSLATE_LIT_H
#define TRANSLATE_LIT_H

#include "core/compiler/ast/ast_node.h"
#include "core/compiler/translator/translator.h"
#include "lib/types.h"

bool translate_lit_node(struct Translator* T, struct ASTNode* node);

#endif /* TRANSLATE_LIT_H */
