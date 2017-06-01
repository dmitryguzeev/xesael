/* File: taste.c */
/* Creation Date: 2017-02-01 */
/* Creator: Dmitry Guzeev <dmitry.guzeev@yahoo.com> */
/* Description: */

#include "taste.h"

#include <stdio.h>
#include <ctype.h>

#include "deps/sil/src/sil.h"

#include "err.h"
#include "args.h"

#include "lib/types.h"
#include "lib/macros.h"
#include "lib/args.h"

#include "core/compiler/compile.h"
#include "core/vm/execute.h"
#include "core/dumper/dumper.h"
#include "core/object/string/string.h"

/*************/
/* Constants */
/*************/

asdstatic const char* __PROMPT = "$>> ";

/**********************/
/* Private prototypes */
/**********************/

static bool __do_repl(void);

/***********/
/* Helpers */
/***********/

static bool __do_repl(void)
{
    /* Print the MOTD */
    printf("Taste REPL " VERSION "\n");

    /* Initialize the SIL state */
    struct SILState sil_state;
    sil_init(&sil_state, __PROMPT);

    /* The actual loop */
    do {
        /* Read the line from the user */
        char* line = sil_read(&sil_state);
        if (line) {
            /* Compile the line */
            struct ByteCode* bc = compile("<stdin>", line);

            /* If we got some error during compile stage */
            if (!bc) {
                /* Report about error */
                err_report();
                /* Delete the line */
                free(line);
                continue;
            }

            /* Execute the byte-code */
            bool res = execute(bc);

            /* If we got some error during execution stage */
            if (!res) {
                /* Report about error */
                err_report();
            }

            /* Delete the line */
            free(line);
        }
    } while (sil_errno == SIL_OK);

    /* Succeed */
    return true;
}

/********/
/* Main */
/********/

int taste_main(struct Arguments const* args)
{
    /* Obvious check */
    DASSERT(args, "");

    /* Parse the arguments */
    struct TasteArgumentsInfo* arg_info;
    arg_info = taste_parse_args(args);
    if (!arg_info) {
        if (err_is_ok()) {
            /* If we just got something like an nothing in the arguments */
            /* Do Read Eval Print Loop */
            /* Initialize the string object dictionary */
            str_objs_init();
            __do_repl();
        } else {
            /* If we got some invalid arguments */
            err_report();
            return 1;
        }
    }

    str_objs_deinit();

    /* Succeed */
    return 0;
}
