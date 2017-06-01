/* File: translate_unop.h */
/* Creation Date: 2017-01-28 */
/* Creator: Dmitry Guzeev <dmitry.guzeev@yahoo.com> */
/* Description: */
/* translate_unop_node() function */

#ifndef TRANSLATE_UNOP_H
#define TRANSLATE_UNOP_H

#include "lib/types.h"
#include "core/compiler/ast/ast_node.h"

bool translate_unop_node(struct ASTNode* node);

#endif /* TRANSLATE_UNOP_H */
