/*
 * Automatically generated from the files:
 *	src/lx/parser.sid
 * and
 *	src/lx/parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 97 "src/lx/parser.act"


	#include <assert.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <stdio.h>
	#include <errno.h>

	#include <adt/xalloc.h>

	#include <fsm/fsm.h>
	#include <fsm/bool.h>
	#include <fsm/pred.h>
	#include <fsm/graph.h>

	#include <re/re.h>

	#include "libfsm/internal.h"

	#include "lexer.h"
	#include "parser.h"
	#include "ast.h"
	#include "var.h"

	typedef char *               string;
	typedef enum re_cflags       cflags;
	typedef struct fsm *         fsm;
	typedef struct ast_zone *    zone;
	typedef struct ast_mapping * mapping;

	struct act_state {
		enum lx_token lex_tok;
		enum lx_token lex_tok_save;
	};

	struct lex_state {
		struct lx lx;
		struct lx_dynbuf buf;

		/* TODO: use lx's generated conveniences for the pattern buffer */
		struct lx_pos pstart;
		char a[512];
		char *p;
	};

	#define CURRENT_TERMINAL (act_state->lex_tok)
	#define ERROR_TERMINAL   TOK_UNKNOWN
	#define ADVANCE_LEXER    do { act_state->lex_tok = lx_next(&lex_state->lx); } while (0)
	#define SAVE_LEXER(tok)  do { act_state->lex_tok_save = act_state->lex_tok; \
	                              act_state->lex_tok = tok;                     } while (0)
	#define RESTORE_LEXER    do { act_state->lex_tok = act_state->lex_tok_save; } while (0)

	static void
	err(const struct lex_state *lex_state, const char *fmt, ...)
	{
		va_list ap;

		assert(lex_state != NULL);

		va_start(ap, fmt);
		fprintf(stderr, "%u:%u: ",
			lex_state->lx.start.line, lex_state->lx.start.col);
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, "\n");
		va_end(ap);
	}

	static void
	err_expected(const struct lex_state *lex_state, const char *token)
	{
		err(lex_state, "Syntax error: expected %s", token);
		exit(EXIT_FAILURE);
	}

#line 89 "src/lx/parser.c"


#ifndef ERROR_TERMINAL
#error "-s no-numeric-terminals given and ERROR_TERMINAL is not defined"
#endif

/* BEGINNING OF FUNCTION DECLARATIONS */

static void p_list_Hof_Hthings(lex_state, act_state, ast, zone, fsm);
static void p_pattern(lex_state, act_state, zone, fsm *);
static void p_145(lex_state, act_state, ast, zone, fsm, ast *, zone *, fsm *);
static void p_list_Hof_Hthings_C_Cthing(lex_state, act_state, ast, zone, fsm);
static void p_151(lex_state, act_state, zone, fsm, zone *, fsm *);
static void p_162(lex_state, act_state, fsm, fsm *);
static void p_167(lex_state, act_state, zone *, fsm *, fsm *);
static void p_pattern_C_Cbody(lex_state, act_state);
static void p_170(lex_state, act_state, zone *, fsm *, fsm *);
static void p_173(lex_state, act_state, zone *, fsm *, fsm *);
static void p_176(lex_state, act_state, fsm *);
static void p_expr_C_Cprimary_Hexpr(lex_state, act_state, zone, fsm *);
static void p_expr_C_Cpostfix_Hexpr(lex_state, act_state, zone, fsm *);
static void p_expr_C_Cprefix_Hexpr(lex_state, act_state, zone, fsm *);
static void p_expr(lex_state, act_state, zone, fsm *);
static void p_194(lex_state, act_state, ast *, zone *, fsm *, string *);
static void p_token_Hmapping(lex_state, act_state, zone, fsm *, string *);
static void p_expr_C_Cinfix_Hexpr(lex_state, act_state, zone, fsm *);
static void p_214(lex_state, act_state, ast *, zone *, string *, fsm *);
extern void p_lx(lex_state, act_state, ast *);
static void p_103(lex_state, act_state, string *);
static void p_expr_C_Cinfix_Hexpr_C_Ccat_Hexpr(lex_state, act_state, zone, fsm *);
static void p_expr_C_Cinfix_Hexpr_C_Calt_Hexpr(lex_state, act_state, zone, fsm *);
static void p_expr_C_Cinfix_Hexpr_C_Cdot_Hexpr(lex_state, act_state, zone, fsm *);
static void p_expr_C_Cinfix_Hexpr_C_Csub_Hexpr(lex_state, act_state, zone, fsm *);
static void p_125(lex_state, act_state);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
p_list_Hof_Hthings(lex_state lex_state, act_state act_state, ast ZI139, zone ZI140, fsm ZI141)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		ast ZI142;
		zone ZI143;
		fsm ZI144;

		p_list_Hof_Hthings_C_Cthing (lex_state, act_state, ZI139, ZI140, ZI141);
		p_145 (lex_state, act_state, ZI139, ZI140, ZI141, &ZI142, &ZI143, &ZI144);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: err-expected-list */
		{
#line 581 "src/lx/parser.act"

		err_expected(lex_state, "list of mappings, bindings or zones");
	
#line 157 "src/lx/parser.c"
		}
		/* END OF ACTION: err-expected-list */
	}
}

static void
p_pattern(lex_state lex_state, act_state act_state, zone ZIz, fsm *ZOr)
{
	fsm ZIr;

	switch (CURRENT_TERMINAL) {
	case (TOK_IDENT):
		{
			string ZIn;

			/* BEGINNING OF EXTRACT: IDENT */
			{
#line 158 "src/lx/parser.act"

		ZIn = xstrdup(lex_state->buf.a);
		if (ZIn == NULL) {
			perror("xstrdup");
			exit(EXIT_FAILURE);
		}
	
#line 183 "src/lx/parser.c"
			}
			/* END OF EXTRACT: IDENT */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: deref-var */
			{
#line 204 "src/lx/parser.act"

		struct ast_zone *z;

		assert((ZIz) != NULL);
		assert((ZIn) != NULL);

		for (z = (ZIz); z != NULL; z = z->parent) {
			(ZIr) = var_find(z->vl, (ZIn));
			if ((ZIr) != NULL) {
				break;
			}

			if ((ZIz)->parent == NULL) {
				/* TODO: use *err */
				err(lex_state, "No such variable: %s", (ZIn));
				goto ZL1;
			}
		}

		(ZIr) = fsm_clone((ZIr));
		if ((ZIr) == NULL) {
			/* TODO: use *err */
			perror("fsm_clone");
			goto ZL1;
		}
	
#line 216 "src/lx/parser.c"
			}
			/* END OF ACTION: deref-var */
		}
		break;
	case (TOK_TOKEN):
		{
			string ZIt;

			/* BEGINNING OF EXTRACT: TOKEN */
			{
#line 150 "src/lx/parser.act"

		/* TODO: submatch addressing */
		ZIt = xstrdup(lex_state->buf.a + 1); /* +1 for '$' prefix */
		if (ZIt == NULL) {
			perror("xstrdup");
			exit(EXIT_FAILURE);
		}
	
#line 236 "src/lx/parser.c"
			}
			/* END OF EXTRACT: TOKEN */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: deref-token */
			{
#line 231 "src/lx/parser.act"

		const struct ast_mapping *m;

		assert((ZIt) != NULL);

		(ZIr) = re_new_empty();
		if ((ZIr) == NULL) {
			perror("re_new_empty");
			goto ZL1;
		}

		for (m = (ZIz)->ml; m != NULL; m = m->next) {
			struct fsm *fsm;
			struct fsm_state *s;

			if (m->token == NULL) {
				continue;
			}

			if (0 != strcmp(m->token->s, (ZIt))) {
				continue;
			}

			fsm = fsm_clone(m->fsm);
			if (fsm == NULL) {
				perror("fsm_clone");
				goto ZL1;
			}

			/*
			 * We don't want to take these with us, because the output here is a
			 * general-purpose FSM for which no mapping has yet been made,
			 * so that it can be used in expressions as for any pattern.
			 */
			for (s = fsm->sl; s != NULL; s = s->next) {
				s->opaque = NULL;
			}

			(ZIr) = fsm_union((ZIr), fsm);
			if ((ZIr) == NULL) {
				perror("fsm_determinise_opaque");
				goto ZL1;
			}
		}
	
#line 288 "src/lx/parser.c"
			}
			/* END OF ACTION: deref-token */
		}
		break;
	case (TOK_ESC): case (TOK_CHAR): case (TOK_RE): case (TOK_STR):
		{
			p_pattern_C_Cbody (lex_state, act_state);
			p_176 (lex_state, act_state, &ZIr);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
p_145(lex_state lex_state, act_state act_state, ast ZI139, zone ZI140, fsm ZI141, ast *ZO142, zone *ZO143, fsm *ZO144)
{
	ast ZI142;
	zone ZI143;
	fsm ZI144;

ZL2_145:;
	switch (CURRENT_TERMINAL) {
	case (TOK_TOKEN): case (TOK_IDENT): case (TOK_ESC): case (TOK_CHAR):
	case (TOK_RE): case (TOK_STR): case (TOK_LPAREN): case (TOK_TILDE):
	case (TOK_BANG):
		{
			p_list_Hof_Hthings_C_Cthing (lex_state, act_state, ZI139, ZI140, ZI141);
			/* BEGINNING OF INLINE: 145 */
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_145;
			}
			/* END OF INLINE: 145 */
		}
		/*UNREACHED*/
	default:
		{
			ZI142 = ZI139;
			ZI143 = ZI140;
			ZI144 = ZI141;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZO142 = ZI142;
	*ZO143 = ZI143;
	*ZO144 = ZI144;
}

static void
p_list_Hof_Hthings_C_Cthing(lex_state lex_state, act_state act_state, ast ZIa, zone ZIz, fsm ZIexit)
{
	switch (CURRENT_TERMINAL) {
	case (TOK_BANG):
		{
			fsm ZI171;
			fsm ZI168;
			fsm ZI165;
			fsm ZIq;
			zone ZI183;
			fsm ZI184;
			string ZI185;
			fsm ZI186;

			ADVANCE_LEXER;
			p_expr_C_Cprefix_Hexpr (lex_state, act_state, ZIz, &ZI171);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-reverse */
			{
#line 457 "src/lx/parser.act"

		assert((ZI171) != NULL);

		if (!fsm_reverse((ZI171))) {
			perror("fsm_reverse");
			goto ZL1;
		}
	
#line 392 "src/lx/parser.c"
			}
			/* END OF ACTION: op-reverse */
			p_173 (lex_state, act_state, &ZIz, &ZI171, &ZI168);
			p_170 (lex_state, act_state, &ZIz, &ZI168, &ZI165);
			p_167 (lex_state, act_state, &ZIz, &ZI165, &ZIq);
			p_151 (lex_state, act_state, ZIz, ZIq, &ZI183, &ZI184);
			p_103 (lex_state, act_state, &ZI185);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: subtract-exit */
			{
#line 500 "src/lx/parser.act"

		assert((ZI184) != NULL);

		if ((ZIexit) == NULL) {
			(ZI186) = (ZI184);
		} else {
			(ZIexit) = fsm_clone((ZIexit));
			if ((ZIexit) == NULL) {
				perror("fsm_clone");
				goto ZL1;
			}

			(ZI186) = fsm_subtract((ZI184), (ZIexit));
			if ((ZI186) == NULL) {
				perror("fsm_subtract");
				goto ZL1;
			}

			if (!fsm_trim((ZI186))) {
				perror("fsm_trim");
				goto ZL1;
			}
		}
	
#line 431 "src/lx/parser.c"
			}
			/* END OF ACTION: subtract-exit */
			p_214 (lex_state, act_state, &ZIa, &ZIz, &ZI185, &ZI186);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (TOK_IDENT):
		{
			string ZIn;

			/* BEGINNING OF EXTRACT: IDENT */
			{
#line 158 "src/lx/parser.act"

		ZIn = xstrdup(lex_state->buf.a);
		if (ZIn == NULL) {
			perror("xstrdup");
			exit(EXIT_FAILURE);
		}
	
#line 455 "src/lx/parser.c"
			}
			/* END OF EXTRACT: IDENT */
			ADVANCE_LEXER;
			p_194 (lex_state, act_state, &ZIa, &ZIz, &ZIexit, &ZIn);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (TOK_LPAREN):
		{
			fsm ZI188;
			fsm ZI171;
			fsm ZI168;
			fsm ZI165;
			fsm ZIq;
			zone ZI189;
			fsm ZI190;
			string ZI191;
			fsm ZI192;

			ADVANCE_LEXER;
			p_expr (lex_state, act_state, ZIz, &ZI188);
			switch (CURRENT_TERMINAL) {
			case (TOK_RPAREN):
				break;
			case (ERROR_TERMINAL):
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			p_162 (lex_state, act_state, ZI188, &ZI171);
			p_173 (lex_state, act_state, &ZIz, &ZI171, &ZI168);
			p_170 (lex_state, act_state, &ZIz, &ZI168, &ZI165);
			p_167 (lex_state, act_state, &ZIz, &ZI165, &ZIq);
			p_151 (lex_state, act_state, ZIz, ZIq, &ZI189, &ZI190);
			p_103 (lex_state, act_state, &ZI191);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: subtract-exit */
			{
#line 500 "src/lx/parser.act"

		assert((ZI190) != NULL);

		if ((ZIexit) == NULL) {
			(ZI192) = (ZI190);
		} else {
			(ZIexit) = fsm_clone((ZIexit));
			if ((ZIexit) == NULL) {
				perror("fsm_clone");
				goto ZL1;
			}

			(ZI192) = fsm_subtract((ZI190), (ZIexit));
			if ((ZI192) == NULL) {
				perror("fsm_subtract");
				goto ZL1;
			}

			if (!fsm_trim((ZI192))) {
				perror("fsm_trim");
				goto ZL1;
			}
		}
	
#line 527 "src/lx/parser.c"
			}
			/* END OF ACTION: subtract-exit */
			p_214 (lex_state, act_state, &ZIa, &ZIz, &ZI191, &ZI192);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (TOK_TILDE):
		{
			fsm ZI171;
			fsm ZI168;
			fsm ZI165;
			fsm ZIq;
			zone ZI178;
			fsm ZI179;
			string ZI180;
			fsm ZI181;

			ADVANCE_LEXER;
			p_expr_C_Cprefix_Hexpr (lex_state, act_state, ZIz, &ZI171);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-complement */
			{
#line 439 "src/lx/parser.act"

		assert((ZI171) != NULL);

		if (!fsm_complement((ZI171))) {
			perror("fsm_complement");
			goto ZL1;
		}
	
#line 565 "src/lx/parser.c"
			}
			/* END OF ACTION: op-complement */
			p_173 (lex_state, act_state, &ZIz, &ZI171, &ZI168);
			p_170 (lex_state, act_state, &ZIz, &ZI168, &ZI165);
			p_167 (lex_state, act_state, &ZIz, &ZI165, &ZIq);
			p_151 (lex_state, act_state, ZIz, ZIq, &ZI178, &ZI179);
			p_103 (lex_state, act_state, &ZI180);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: subtract-exit */
			{
#line 500 "src/lx/parser.act"

		assert((ZI179) != NULL);

		if ((ZIexit) == NULL) {
			(ZI181) = (ZI179);
		} else {
			(ZIexit) = fsm_clone((ZIexit));
			if ((ZIexit) == NULL) {
				perror("fsm_clone");
				goto ZL1;
			}

			(ZI181) = fsm_subtract((ZI179), (ZIexit));
			if ((ZI181) == NULL) {
				perror("fsm_subtract");
				goto ZL1;
			}

			if (!fsm_trim((ZI181))) {
				perror("fsm_trim");
				goto ZL1;
			}
		}
	
#line 604 "src/lx/parser.c"
			}
			/* END OF ACTION: subtract-exit */
			p_214 (lex_state, act_state, &ZIa, &ZIz, &ZI180, &ZI181);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (TOK_TOKEN):
		{
			string ZI195;
			fsm ZI196;
			fsm ZI171;
			fsm ZI168;
			fsm ZI165;
			fsm ZIq;
			zone ZI197;
			fsm ZI198;
			string ZI199;
			fsm ZI200;

			/* BEGINNING OF EXTRACT: TOKEN */
			{
#line 150 "src/lx/parser.act"

		/* TODO: submatch addressing */
		ZI195 = xstrdup(lex_state->buf.a + 1); /* +1 for '$' prefix */
		if (ZI195 == NULL) {
			perror("xstrdup");
			exit(EXIT_FAILURE);
		}
	
#line 638 "src/lx/parser.c"
			}
			/* END OF EXTRACT: TOKEN */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: deref-token */
			{
#line 231 "src/lx/parser.act"

		const struct ast_mapping *m;

		assert((ZI195) != NULL);

		(ZI196) = re_new_empty();
		if ((ZI196) == NULL) {
			perror("re_new_empty");
			goto ZL1;
		}

		for (m = (ZIz)->ml; m != NULL; m = m->next) {
			struct fsm *fsm;
			struct fsm_state *s;

			if (m->token == NULL) {
				continue;
			}

			if (0 != strcmp(m->token->s, (ZI195))) {
				continue;
			}

			fsm = fsm_clone(m->fsm);
			if (fsm == NULL) {
				perror("fsm_clone");
				goto ZL1;
			}

			/*
			 * We don't want to take these with us, because the output here is a
			 * general-purpose FSM for which no mapping has yet been made,
			 * so that it can be used in expressions as for any pattern.
			 */
			for (s = fsm->sl; s != NULL; s = s->next) {
				s->opaque = NULL;
			}

			(ZI196) = fsm_union((ZI196), fsm);
			if ((ZI196) == NULL) {
				perror("fsm_determinise_opaque");
				goto ZL1;
			}
		}
	
#line 690 "src/lx/parser.c"
			}
			/* END OF ACTION: deref-token */
			p_162 (lex_state, act_state, ZI196, &ZI171);
			p_173 (lex_state, act_state, &ZIz, &ZI171, &ZI168);
			p_170 (lex_state, act_state, &ZIz, &ZI168, &ZI165);
			p_167 (lex_state, act_state, &ZIz, &ZI165, &ZIq);
			p_151 (lex_state, act_state, ZIz, ZIq, &ZI197, &ZI198);
			p_103 (lex_state, act_state, &ZI199);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: subtract-exit */
			{
#line 500 "src/lx/parser.act"

		assert((ZI198) != NULL);

		if ((ZIexit) == NULL) {
			(ZI200) = (ZI198);
		} else {
			(ZIexit) = fsm_clone((ZIexit));
			if ((ZIexit) == NULL) {
				perror("fsm_clone");
				goto ZL1;
			}

			(ZI200) = fsm_subtract((ZI198), (ZIexit));
			if ((ZI200) == NULL) {
				perror("fsm_subtract");
				goto ZL1;
			}

			if (!fsm_trim((ZI200))) {
				perror("fsm_trim");
				goto ZL1;
			}
		}
	
#line 730 "src/lx/parser.c"
			}
			/* END OF ACTION: subtract-exit */
			p_214 (lex_state, act_state, &ZIa, &ZIz, &ZI199, &ZI200);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (TOK_ESC): case (TOK_CHAR): case (TOK_RE): case (TOK_STR):
		{
			fsm ZI202;
			fsm ZI171;
			fsm ZI168;
			fsm ZI165;
			fsm ZIq;
			zone ZI203;
			fsm ZI204;
			string ZI205;
			fsm ZI206;

			p_pattern_C_Cbody (lex_state, act_state);
			p_176 (lex_state, act_state, &ZI202);
			p_162 (lex_state, act_state, ZI202, &ZI171);
			p_173 (lex_state, act_state, &ZIz, &ZI171, &ZI168);
			p_170 (lex_state, act_state, &ZIz, &ZI168, &ZI165);
			p_167 (lex_state, act_state, &ZIz, &ZI165, &ZIq);
			p_151 (lex_state, act_state, ZIz, ZIq, &ZI203, &ZI204);
			p_103 (lex_state, act_state, &ZI205);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: subtract-exit */
			{
#line 500 "src/lx/parser.act"

		assert((ZI204) != NULL);

		if ((ZIexit) == NULL) {
			(ZI206) = (ZI204);
		} else {
			(ZIexit) = fsm_clone((ZIexit));
			if ((ZIexit) == NULL) {
				perror("fsm_clone");
				goto ZL1;
			}

			(ZI206) = fsm_subtract((ZI204), (ZIexit));
			if ((ZI206) == NULL) {
				perror("fsm_subtract");
				goto ZL1;
			}

			if (!fsm_trim((ZI206))) {
				perror("fsm_trim");
				goto ZL1;
			}
		}
	
#line 791 "src/lx/parser.c"
			}
			/* END OF ACTION: subtract-exit */
			p_214 (lex_state, act_state, &ZIa, &ZIz, &ZI205, &ZI206);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: err-expected-thing */
		{
#line 577 "src/lx/parser.act"

		err_expected(lex_state, "mapping, binding or zone");
	
#line 815 "src/lx/parser.c"
		}
		/* END OF ACTION: err-expected-thing */
	}
}

static void
p_151(lex_state lex_state, act_state act_state, zone ZI147, fsm ZI148, zone *ZO149, fsm *ZO150)
{
	zone ZI149;
	fsm ZI150;

ZL2_151:;
	switch (CURRENT_TERMINAL) {
	case (TOK_PIPE):
		{
			fsm ZIb;
			fsm ZIq;

			ADVANCE_LEXER;
			p_expr_C_Cinfix_Hexpr_C_Csub_Hexpr (lex_state, act_state, ZI147, &ZIb);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-alt */
			{
#line 495 "src/lx/parser.act"

		fprintf(stderr, "unimplemented\n");
		(ZIq) = NULL;
		goto ZL1;
	
#line 848 "src/lx/parser.c"
			}
			/* END OF ACTION: op-alt */
			/* BEGINNING OF INLINE: 151 */
			ZI148 = ZIq;
			goto ZL2_151;
			/* END OF INLINE: 151 */
		}
		/*UNREACHED*/
	default:
		{
			ZI149 = ZI147;
			ZI150 = ZI148;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZO149 = ZI149;
	*ZO150 = ZI150;
}

static void
p_162(lex_state lex_state, act_state act_state, fsm ZI156, fsm *ZO161)
{
	fsm ZI161;

ZL2_162:;
	switch (CURRENT_TERMINAL) {
	case (TOK_STAR): case (TOK_CROSS): case (TOK_QMARK):
		{
			fsm ZIq;

			ZIq = ZI156;
			/* BEGINNING OF INLINE: 208 */
			{
				switch (CURRENT_TERMINAL) {
				case (TOK_CROSS):
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: op-cross */
						{
#line 430 "src/lx/parser.act"

		fprintf(stderr, "unimplemented\n");
		goto ZL1;
	
#line 900 "src/lx/parser.c"
						}
						/* END OF ACTION: op-cross */
						/* BEGINNING OF INLINE: 162 */
						ZI156 = ZIq;
						goto ZL2_162;
						/* END OF INLINE: 162 */
					}
					/*UNREACHED*/
				case (TOK_QMARK):
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: op-qmark */
						{
#line 435 "src/lx/parser.act"

		fprintf(stderr, "unimplemented\n");
		goto ZL1;
	
#line 919 "src/lx/parser.c"
						}
						/* END OF ACTION: op-qmark */
						/* BEGINNING OF INLINE: 162 */
						ZI156 = ZIq;
						goto ZL2_162;
						/* END OF INLINE: 162 */
					}
					/*UNREACHED*/
				case (TOK_STAR):
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: op-star */
						{
#line 425 "src/lx/parser.act"

		fprintf(stderr, "unimplemented\n");
		goto ZL1;
	
#line 938 "src/lx/parser.c"
						}
						/* END OF ACTION: op-star */
						/* BEGINNING OF INLINE: 162 */
						ZI156 = ZIq;
						goto ZL2_162;
						/* END OF INLINE: 162 */
					}
					/*UNREACHED*/
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 208 */
		}
		/*UNREACHED*/
	default:
		{
			ZI161 = ZI156;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZO161 = ZI161;
}

static void
p_167(lex_state lex_state, act_state act_state, zone *ZIz, fsm *ZI165, fsm *ZOq)
{
	fsm ZIq;

	switch (CURRENT_TERMINAL) {
	case (TOK_DASH):
		{
			fsm ZIb;

			ADVANCE_LEXER;
			p_expr_C_Cinfix_Hexpr_C_Csub_Hexpr (lex_state, act_state, *ZIz, &ZIb);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-subtract */
			{
#line 483 "src/lx/parser.act"

		assert((*ZI165) != NULL);
		assert((ZIb) != NULL);

		(ZIq) = fsm_subtract((*ZI165), (ZIb));
		if ((ZIq) == NULL) {
			perror("fsm_subtract");
			goto ZL1;
		}
	
#line 999 "src/lx/parser.c"
			}
			/* END OF ACTION: op-subtract */
		}
		break;
	default:
		{
			ZIq = *ZI165;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_pattern_C_Cbody(lex_state lex_state, act_state act_state)
{
ZL2_pattern_C_Cbody:;
	switch (CURRENT_TERMINAL) {
	case (TOK_CHAR):
		{
			char ZIc;

			/* BEGINNING OF EXTRACT: CHAR */
			{
#line 140 "src/lx/parser.act"

		assert(lex_state->buf.a[0] != '\0');
		assert(lex_state->buf.a[1] == '\0');

		ZIc = lex_state->buf.a[0];

		/* position of first character */
		if (lex_state->p == lex_state->a) {
			lex_state->pstart = lex_state->lx.start;
		}
	
#line 1043 "src/lx/parser.c"
			}
			/* END OF EXTRACT: CHAR */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: pattern-char */
			{
#line 180 "src/lx/parser.act"

		/* TODO */
		*lex_state->p++ = (ZIc);
	
#line 1054 "src/lx/parser.c"
			}
			/* END OF ACTION: pattern-char */
			/* BEGINNING OF INLINE: pattern::body */
			goto ZL2_pattern_C_Cbody;
			/* END OF INLINE: pattern::body */
		}
		/*UNREACHED*/
	case (TOK_ESC):
		{
			char ZIc;

			/* BEGINNING OF EXTRACT: ESC */
			{
#line 119 "src/lx/parser.act"

		assert(lex_state->buf.a[0] == '\\');
		assert(lex_state->buf.a[1] != '\0');
		assert(lex_state->buf.a[2] == '\0');

		switch (lex_state->buf.a[1]) {
		case '\\': ZIc = '\\'; break;
		case '\"': ZIc = '\"'; break;
		case 'f':  ZIc = '\f'; break;
		case 'n':  ZIc = '\n'; break;
		case 'r':  ZIc = '\r'; break;
		case 't':  ZIc = '\t'; break;
		case 'v':  ZIc = '\v'; break;

		default:   ZIc = '\0'; break; /* TODO: handle error */
		}

		/* position of first character */
		if (lex_state->p == lex_state->a) {
			lex_state->pstart = lex_state->lx.start;
		}
	
#line 1091 "src/lx/parser.c"
			}
			/* END OF EXTRACT: ESC */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: pattern-char */
			{
#line 180 "src/lx/parser.act"

		/* TODO */
		*lex_state->p++ = (ZIc);
	
#line 1102 "src/lx/parser.c"
			}
			/* END OF ACTION: pattern-char */
			/* BEGINNING OF INLINE: pattern::body */
			goto ZL2_pattern_C_Cbody;
			/* END OF INLINE: pattern::body */
		}
		/*UNREACHED*/
	case (ERROR_TERMINAL):
		return;
	default:
		break;
	}
}

static void
p_170(lex_state lex_state, act_state act_state, zone *ZIz, fsm *ZI168, fsm *ZOq)
{
	fsm ZIq;

	switch (CURRENT_TERMINAL) {
	case (TOK_TOKEN): case (TOK_IDENT): case (TOK_ESC): case (TOK_CHAR):
	case (TOK_RE): case (TOK_STR): case (TOK_LPAREN): case (TOK_TILDE):
	case (TOK_BANG):
		{
			fsm ZIb;

			p_expr_C_Cinfix_Hexpr_C_Ccat_Hexpr (lex_state, act_state, *ZIz, &ZIb);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-concat */
			{
#line 466 "src/lx/parser.act"

		assert((*ZI168) != NULL);
		assert((ZIb) != NULL);

		(ZIq) = fsm_concat((*ZI168), (ZIb));
		if ((ZIq) == NULL) {
			perror("fsm_concat");
			goto ZL1;
		}
	
#line 1147 "src/lx/parser.c"
			}
			/* END OF ACTION: op-concat */
		}
		break;
	default:
		{
			ZIq = *ZI168;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_173(lex_state lex_state, act_state act_state, zone *ZIz, fsm *ZI171, fsm *ZOq)
{
	fsm ZIq;

	switch (CURRENT_TERMINAL) {
	case (TOK_DOT):
		{
			fsm ZIb;

			ADVANCE_LEXER;
			p_expr_C_Cinfix_Hexpr_C_Cdot_Hexpr (lex_state, act_state, *ZIz, &ZIb);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-product */
			{
#line 478 "src/lx/parser.act"

		fprintf(stderr, "unimplemented\n");
		(ZIq) = NULL;
		goto ZL1;
	
#line 1192 "src/lx/parser.c"
			}
			/* END OF ACTION: op-product */
		}
		break;
	default:
		{
			ZIq = *ZI171;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_176(lex_state lex_state, act_state act_state, fsm *ZOr)
{
	fsm ZIr;

	switch (CURRENT_TERMINAL) {
	case (TOK_RE):
		{
			cflags ZIf;
			string ZIs;

			/* BEGINNING OF EXTRACT: RE */
			{
#line 170 "src/lx/parser.act"

		assert(lex_state->buf.a[0] == '/');

		/* TODO: submatch addressing */

		if (-1 == re_cflags(lex_state->buf.a + 1, &ZIf)) { /* TODO: +1 for '/' prefix */
			err(lex_state, "/%s: Unrecognised regexp flags", lex_state->buf.a + 1);
			exit(EXIT_FAILURE);
		}
	
#line 1237 "src/lx/parser.c"
			}
			/* END OF EXTRACT: RE */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: pattern-buffer */
			{
#line 192 "src/lx/parser.act"

		/* TODO */
		*lex_state->p++ = '\0';

		/*
		 * Note we strdup() here because the grammar permits adjacent patterns,
		 * and so the pattern buffer will be overwritten by the LL(1) one-token
		 * lookahead.
		 */
		(ZIs) = xstrdup(lex_state->a);
		if ((ZIs) == NULL) {
			perror("xstrdup");
			exit(EXIT_FAILURE);
		}

		lex_state->p = lex_state->a;
	
#line 1261 "src/lx/parser.c"
			}
			/* END OF ACTION: pattern-buffer */
			/* BEGINNING OF ACTION: compile-regex */
			{
#line 295 "src/lx/parser.act"

		struct re_err err;
		const char *s;

		assert((ZIs) != NULL);

		s = (ZIs);

		(ZIr) = re_new_comp(RE_SIMPLE, re_getc_str, &s, (ZIf), &err);
		if ((ZIr) == NULL) {
			assert(err.e != RE_EBADFORM);
			/* TODO: pass filename for .lx source */
			re_perror("re_new_comp", RE_SIMPLE, &err, NULL, (ZIs));
			exit(EXIT_FAILURE);
		}
	
#line 1283 "src/lx/parser.c"
			}
			/* END OF ACTION: compile-regex */
			/* BEGINNING OF ACTION: free */
			{
#line 535 "src/lx/parser.act"

		free((ZIs));
	
#line 1292 "src/lx/parser.c"
			}
			/* END OF ACTION: free */
		}
		break;
	case (TOK_STR):
		{
			string ZIs;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: pattern-buffer */
			{
#line 192 "src/lx/parser.act"

		/* TODO */
		*lex_state->p++ = '\0';

		/*
		 * Note we strdup() here because the grammar permits adjacent patterns,
		 * and so the pattern buffer will be overwritten by the LL(1) one-token
		 * lookahead.
		 */
		(ZIs) = xstrdup(lex_state->a);
		if ((ZIs) == NULL) {
			perror("xstrdup");
			exit(EXIT_FAILURE);
		}

		lex_state->p = lex_state->a;
	
#line 1322 "src/lx/parser.c"
			}
			/* END OF ACTION: pattern-buffer */
			/* BEGINNING OF ACTION: compile-literal */
			{
#line 278 "src/lx/parser.act"

		struct re_err err;
		const char *s;

		assert((ZIs) != NULL);

		s = (ZIs);

		(ZIr) = re_new_comp(RE_LITERAL, re_getc_str, &s, 0, &err);
		if ((ZIr) == NULL) {
			assert(err.e != RE_EBADFORM);
			/* TODO: pass filename for .lx source */
			re_perror("re_new_comp", RE_LITERAL, &err, NULL, (ZIs));
			exit(EXIT_FAILURE);
		}
	
#line 1344 "src/lx/parser.c"
			}
			/* END OF ACTION: compile-literal */
			/* BEGINNING OF ACTION: free */
			{
#line 535 "src/lx/parser.act"

		free((ZIs));
	
#line 1353 "src/lx/parser.c"
			}
			/* END OF ACTION: free */
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
p_expr_C_Cprimary_Hexpr(lex_state lex_state, act_state act_state, zone ZIz, fsm *ZOq)
{
	fsm ZIq;

	switch (CURRENT_TERMINAL) {
	case (TOK_LPAREN):
		{
			ADVANCE_LEXER;
			p_expr (lex_state, act_state, ZIz, &ZIq);
			switch (CURRENT_TERMINAL) {
			case (TOK_RPAREN):
				break;
			case (ERROR_TERMINAL):
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case (TOK_TOKEN): case (TOK_IDENT): case (TOK_ESC): case (TOK_CHAR):
	case (TOK_RE): case (TOK_STR):
		{
			p_pattern (lex_state, act_state, ZIz, &ZIq);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_expr_C_Cpostfix_Hexpr(lex_state lex_state, act_state act_state, zone ZI153, fsm *ZO161)
{
	fsm ZI161;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		fsm ZIq;

		p_expr_C_Cprimary_Hexpr (lex_state, act_state, ZI153, &ZIq);
		p_162 (lex_state, act_state, ZIq, &ZI161);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZO161 = ZI161;
}

static void
p_expr_C_Cprefix_Hexpr(lex_state lex_state, act_state act_state, zone ZIz, fsm *ZOq)
{
	fsm ZIq;

	switch (CURRENT_TERMINAL) {
	case (TOK_BANG):
		{
			ADVANCE_LEXER;
			p_expr_C_Cprefix_Hexpr (lex_state, act_state, ZIz, &ZIq);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-reverse */
			{
#line 457 "src/lx/parser.act"

		assert((ZIq) != NULL);

		if (!fsm_reverse((ZIq))) {
			perror("fsm_reverse");
			goto ZL1;
		}
	
#line 1467 "src/lx/parser.c"
			}
			/* END OF ACTION: op-reverse */
		}
		break;
	case (TOK_TILDE):
		{
			ADVANCE_LEXER;
			p_expr_C_Cprefix_Hexpr (lex_state, act_state, ZIz, &ZIq);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-complement */
			{
#line 439 "src/lx/parser.act"

		assert((ZIq) != NULL);

		if (!fsm_complement((ZIq))) {
			perror("fsm_complement");
			goto ZL1;
		}
	
#line 1491 "src/lx/parser.c"
			}
			/* END OF ACTION: op-complement */
		}
		break;
	case (TOK_TOKEN): case (TOK_IDENT): case (TOK_ESC): case (TOK_CHAR):
	case (TOK_RE): case (TOK_STR): case (TOK_LPAREN):
		{
			p_expr_C_Cpostfix_Hexpr (lex_state, act_state, ZIz, &ZIq);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_expr(lex_state lex_state, act_state act_state, zone ZIz, fsm *ZOq)
{
	fsm ZIq;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		p_expr_C_Cinfix_Hexpr (lex_state, act_state, ZIz, &ZIq);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_194(lex_state lex_state, act_state act_state, ast *ZIa, zone *ZIz, fsm *ZIexit, string *ZIn)
{
	switch (CURRENT_TERMINAL) {
	case (TOK_BIND):
		{
			fsm ZIr;
			fsm ZIq;

			/* BEGINNING OF INLINE: 112 */
			{
				{
					switch (CURRENT_TERMINAL) {
					case (TOK_BIND):
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: err-expected-bind */
					{
#line 553 "src/lx/parser.act"

		err_expected(lex_state, "'='");
	
#line 1571 "src/lx/parser.c"
					}
					/* END OF ACTION: err-expected-bind */
				}
			ZL2:;
			}
			/* END OF INLINE: 112 */
			p_expr (lex_state, act_state, *ZIz, &ZIr);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: subtract-exit */
			{
#line 500 "src/lx/parser.act"

		assert((ZIr) != NULL);

		if ((*ZIexit) == NULL) {
			(ZIq) = (ZIr);
		} else {
			(*ZIexit) = fsm_clone((*ZIexit));
			if ((*ZIexit) == NULL) {
				perror("fsm_clone");
				goto ZL1;
			}

			(ZIq) = fsm_subtract((ZIr), (*ZIexit));
			if ((ZIq) == NULL) {
				perror("fsm_subtract");
				goto ZL1;
			}

			if (!fsm_trim((ZIq))) {
				perror("fsm_trim");
				goto ZL1;
			}
		}
	
#line 1610 "src/lx/parser.c"
			}
			/* END OF ACTION: subtract-exit */
			p_125 (lex_state, act_state);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: add-binding */
			{
#line 390 "src/lx/parser.act"

		struct var *v;

		assert((*ZIa) != NULL);
		assert((*ZIz) != NULL);
		assert((*ZIn) != NULL);
		assert((ZIq) != NULL);

		(void) (*ZIa);

		v = var_bind(&(*ZIz)->vl, (*ZIn), (ZIq));
		if (v == NULL) {
			perror("var_bind");
			goto ZL1;
		}
	
#line 1637 "src/lx/parser.c"
			}
			/* END OF ACTION: add-binding */
		}
		break;
	case (TOK_TOKEN): case (TOK_IDENT): case (TOK_ESC): case (TOK_CHAR):
	case (TOK_RE): case (TOK_STR): case (TOK_SEMI): case (TOK_TO):
	case (TOK_MAP): case (TOK_LPAREN): case (TOK_STAR): case (TOK_CROSS):
	case (TOK_QMARK): case (TOK_TILDE): case (TOK_DASH): case (TOK_BANG):
	case (TOK_DOT): case (TOK_PIPE):
		{
			fsm ZI209;
			fsm ZI171;
			fsm ZI168;
			fsm ZI165;
			fsm ZIq;
			zone ZI210;
			fsm ZI211;
			string ZI212;
			fsm ZI213;

			/* BEGINNING OF ACTION: deref-var */
			{
#line 204 "src/lx/parser.act"

		struct ast_zone *z;

		assert((*ZIz) != NULL);
		assert((*ZIn) != NULL);

		for (z = (*ZIz); z != NULL; z = z->parent) {
			(ZI209) = var_find(z->vl, (*ZIn));
			if ((ZI209) != NULL) {
				break;
			}

			if ((*ZIz)->parent == NULL) {
				/* TODO: use *err */
				err(lex_state, "No such variable: %s", (*ZIn));
				goto ZL1;
			}
		}

		(ZI209) = fsm_clone((ZI209));
		if ((ZI209) == NULL) {
			/* TODO: use *err */
			perror("fsm_clone");
			goto ZL1;
		}
	
#line 1687 "src/lx/parser.c"
			}
			/* END OF ACTION: deref-var */
			p_162 (lex_state, act_state, ZI209, &ZI171);
			p_173 (lex_state, act_state, ZIz, &ZI171, &ZI168);
			p_170 (lex_state, act_state, ZIz, &ZI168, &ZI165);
			p_167 (lex_state, act_state, ZIz, &ZI165, &ZIq);
			p_151 (lex_state, act_state, *ZIz, ZIq, &ZI210, &ZI211);
			p_103 (lex_state, act_state, &ZI212);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: subtract-exit */
			{
#line 500 "src/lx/parser.act"

		assert((ZI211) != NULL);

		if ((*ZIexit) == NULL) {
			(ZI213) = (ZI211);
		} else {
			(*ZIexit) = fsm_clone((*ZIexit));
			if ((*ZIexit) == NULL) {
				perror("fsm_clone");
				goto ZL1;
			}

			(ZI213) = fsm_subtract((ZI211), (*ZIexit));
			if ((ZI213) == NULL) {
				perror("fsm_subtract");
				goto ZL1;
			}

			if (!fsm_trim((ZI213))) {
				perror("fsm_trim");
				goto ZL1;
			}
		}
	
#line 1727 "src/lx/parser.c"
			}
			/* END OF ACTION: subtract-exit */
			p_214 (lex_state, act_state, ZIa, ZIz, &ZI212, &ZI213);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
p_token_Hmapping(lex_state lex_state, act_state act_state, zone ZIz, fsm *ZOr, string *ZOt)
{
	fsm ZIr;
	string ZIt;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		p_expr (lex_state, act_state, ZIz, &ZIr);
		p_103 (lex_state, act_state, &ZIt);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOr = ZIr;
	*ZOt = ZIt;
}

static void
p_expr_C_Cinfix_Hexpr(lex_state lex_state, act_state act_state, zone ZIz, fsm *ZOq)
{
	fsm ZIq;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		p_expr_C_Cinfix_Hexpr_C_Calt_Hexpr (lex_state, act_state, ZIz, &ZIq);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_214(lex_state lex_state, act_state act_state, ast *ZIa, zone *ZIz, string *ZI212, fsm *ZI213)
{
	switch (CURRENT_TERMINAL) {
	case (TOK_TO):
		{
			fsm ZIr2;
			string ZIt2;
			zone ZIchild;

			/* BEGINNING OF INLINE: 120 */
			{
				{
					switch (CURRENT_TERMINAL) {
					case (TOK_TO):
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: err-expected-to */
					{
#line 561 "src/lx/parser.act"

		err_expected(lex_state, "'..'");
	
#line 1827 "src/lx/parser.c"
					}
					/* END OF ACTION: err-expected-to */
				}
			ZL2:;
			}
			/* END OF INLINE: 120 */
			p_token_Hmapping (lex_state, act_state, *ZIz, &ZIr2, &ZIt2);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-zone */
			{
#line 352 "src/lx/parser.act"

		assert((*ZIa) != NULL);

		(ZIchild) = ast_addzone((*ZIa), (*ZIz));
		if ((ZIchild) == NULL) {
			perror("ast_addzone");
			goto ZL1;
		}
	
#line 1851 "src/lx/parser.c"
			}
			/* END OF ACTION: make-zone */
			/* BEGINNING OF INLINE: 124 */
			{
				switch (CURRENT_TERMINAL) {
				case (TOK_SEMI):
					{
						zone ZIx;
						string ZIy;
						fsm ZIu;
						fsm ZIw;
						fsm ZIv;

						p_125 (lex_state, act_state);
						if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
							RESTORE_LEXER;
							goto ZL5;
						}
						/* BEGINNING OF ACTION: no-zone */
						{
#line 420 "src/lx/parser.act"

		(ZIx) = NULL;
	
#line 1876 "src/lx/parser.c"
						}
						/* END OF ACTION: no-zone */
						/* BEGINNING OF ACTION: no-token */
						{
#line 412 "src/lx/parser.act"

		(ZIy) = NULL;
	
#line 1885 "src/lx/parser.c"
						}
						/* END OF ACTION: no-token */
						/* BEGINNING OF ACTION: clone */
						{
#line 525 "src/lx/parser.act"

		assert((ZIr2) != NULL);

		(ZIu) = fsm_clone((ZIr2));
		if ((ZIu) == NULL) {
			perror("fsm_clone");
			goto ZL5;
		}
	
#line 1900 "src/lx/parser.c"
						}
						/* END OF ACTION: clone */
						/* BEGINNING OF ACTION: regex-any */
						{
#line 323 "src/lx/parser.act"

		struct fsm_state *e;

		(ZIw) = re_new_empty();
		if ((ZIw) == NULL) {
			perror("re_new_empty");
			goto ZL5;
		}

		e = fsm_addstate((ZIw));
		if (e == NULL) {
			perror("fsm_addstate");
			goto ZL5;
		}

		if (!fsm_addedge_any((ZIw), fsm_getstart((ZIw)), e)) {
			perror("fsm_addedge_any");
			goto ZL5;
		}

		fsm_setend((ZIw), e, 1);
	
#line 1928 "src/lx/parser.c"
						}
						/* END OF ACTION: regex-any */
						/* BEGINNING OF ACTION: subtract-exit */
						{
#line 500 "src/lx/parser.act"

		assert((ZIw) != NULL);

		if ((ZIu) == NULL) {
			(ZIv) = (ZIw);
		} else {
			(ZIu) = fsm_clone((ZIu));
			if ((ZIu) == NULL) {
				perror("fsm_clone");
				goto ZL5;
			}

			(ZIv) = fsm_subtract((ZIw), (ZIu));
			if ((ZIv) == NULL) {
				perror("fsm_subtract");
				goto ZL5;
			}

			if (!fsm_trim((ZIv))) {
				perror("fsm_trim");
				goto ZL5;
			}
		}
	
#line 1958 "src/lx/parser.c"
						}
						/* END OF ACTION: subtract-exit */
						/* BEGINNING OF ACTION: add-mapping */
						{
#line 365 "src/lx/parser.act"

		struct ast_token *t;
		struct ast_mapping *m;

		assert((*ZIa) != NULL);
		assert((ZIchild) != NULL);
		assert((ZIchild) != (ZIx));
		assert((ZIv) != NULL);

		if ((ZIy) != NULL) {
			t = ast_addtoken((*ZIa), (ZIy));
			if (t == NULL) {
				perror("ast_addtoken");
				goto ZL5;
			}
		} else {
			t = NULL;
		}

		m = ast_addmapping((ZIchild), (ZIv), t, (ZIx));
		if (m == NULL) {
			perror("ast_addmapping");
			goto ZL5;
		}
	
#line 1989 "src/lx/parser.c"
						}
						/* END OF ACTION: add-mapping */
					}
					break;
				case (TOK_OPEN):
					{
						/* BEGINNING OF INLINE: 131 */
						{
							{
								switch (CURRENT_TERMINAL) {
								case (TOK_OPEN):
									break;
								default:
									goto ZL7;
								}
								ADVANCE_LEXER;
							}
							goto ZL6;
						ZL7:;
							{
								/* BEGINNING OF ACTION: err-expected-open */
								{
#line 565 "src/lx/parser.act"

		err_expected(lex_state, "'{'");
	
#line 2016 "src/lx/parser.c"
								}
								/* END OF ACTION: err-expected-open */
							}
						ZL6:;
						}
						/* END OF INLINE: 131 */
						p_list_Hof_Hthings (lex_state, act_state, *ZIa, ZIchild, ZIr2);
						/* BEGINNING OF INLINE: 132 */
						{
							if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
								RESTORE_LEXER;
								goto ZL5;
							}
							{
								switch (CURRENT_TERMINAL) {
								case (TOK_CLOSE):
									break;
								default:
									goto ZL9;
								}
								ADVANCE_LEXER;
							}
							goto ZL8;
						ZL9:;
							{
								/* BEGINNING OF ACTION: err-expected-close */
								{
#line 569 "src/lx/parser.act"

		err_expected(lex_state, "'}'");
	
#line 2048 "src/lx/parser.c"
								}
								/* END OF ACTION: err-expected-close */
							}
						ZL8:;
						}
						/* END OF INLINE: 132 */
					}
					break;
				default:
					goto ZL5;
				}
				goto ZL4;
			ZL5:;
				{
					/* BEGINNING OF ACTION: err-expected-list */
					{
#line 581 "src/lx/parser.act"

		err_expected(lex_state, "list of mappings, bindings or zones");
	
#line 2069 "src/lx/parser.c"
					}
					/* END OF ACTION: err-expected-list */
				}
			ZL4:;
			}
			/* END OF INLINE: 124 */
			/* BEGINNING OF ACTION: add-mapping */
			{
#line 365 "src/lx/parser.act"

		struct ast_token *t;
		struct ast_mapping *m;

		assert((*ZIa) != NULL);
		assert((*ZIz) != NULL);
		assert((*ZIz) != (ZIchild));
		assert((*ZI213) != NULL);

		if ((*ZI212) != NULL) {
			t = ast_addtoken((*ZIa), (*ZI212));
			if (t == NULL) {
				perror("ast_addtoken");
				goto ZL1;
			}
		} else {
			t = NULL;
		}

		m = ast_addmapping((*ZIz), (*ZI213), t, (ZIchild));
		if (m == NULL) {
			perror("ast_addmapping");
			goto ZL1;
		}
	
#line 2104 "src/lx/parser.c"
			}
			/* END OF ACTION: add-mapping */
			/* BEGINNING OF ACTION: add-mapping */
			{
#line 365 "src/lx/parser.act"

		struct ast_token *t;
		struct ast_mapping *m;

		assert((*ZIa) != NULL);
		assert((ZIchild) != NULL);
		assert((ZIchild) != (*ZIz));
		assert((ZIr2) != NULL);

		if ((ZIt2) != NULL) {
			t = ast_addtoken((*ZIa), (ZIt2));
			if (t == NULL) {
				perror("ast_addtoken");
				goto ZL1;
			}
		} else {
			t = NULL;
		}

		m = ast_addmapping((ZIchild), (ZIr2), t, (*ZIz));
		if (m == NULL) {
			perror("ast_addmapping");
			goto ZL1;
		}
	
#line 2135 "src/lx/parser.c"
			}
			/* END OF ACTION: add-mapping */
		}
		break;
	case (TOK_SEMI):
		{
			zone ZIto;

			p_125 (lex_state, act_state);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: no-zone */
			{
#line 420 "src/lx/parser.act"

		(ZIto) = NULL;
	
#line 2155 "src/lx/parser.c"
			}
			/* END OF ACTION: no-zone */
			/* BEGINNING OF ACTION: add-mapping */
			{
#line 365 "src/lx/parser.act"

		struct ast_token *t;
		struct ast_mapping *m;

		assert((*ZIa) != NULL);
		assert((*ZIz) != NULL);
		assert((*ZIz) != (ZIto));
		assert((*ZI213) != NULL);

		if ((*ZI212) != NULL) {
			t = ast_addtoken((*ZIa), (*ZI212));
			if (t == NULL) {
				perror("ast_addtoken");
				goto ZL1;
			}
		} else {
			t = NULL;
		}

		m = ast_addmapping((*ZIz), (*ZI213), t, (ZIto));
		if (m == NULL) {
			perror("ast_addmapping");
			goto ZL1;
		}
	
#line 2186 "src/lx/parser.c"
			}
			/* END OF ACTION: add-mapping */
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

void
p_lx(lex_state lex_state, act_state act_state, ast *ZOa)
{
	ast ZIa;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		zone ZIparent;
		zone ZIz;
		fsm ZIexit;

		/* BEGINNING OF ACTION: no-zone */
		{
#line 420 "src/lx/parser.act"

		(ZIparent) = NULL;
	
#line 2221 "src/lx/parser.c"
		}
		/* END OF ACTION: no-zone */
		/* BEGINNING OF ACTION: make-ast */
		{
#line 344 "src/lx/parser.act"

		(ZIa) = ast_new();
		if ((ZIa) == NULL) {
			perror("ast_new");
			goto ZL1;
		}
	
#line 2234 "src/lx/parser.c"
		}
		/* END OF ACTION: make-ast */
		/* BEGINNING OF ACTION: make-zone */
		{
#line 352 "src/lx/parser.act"

		assert((ZIa) != NULL);

		(ZIz) = ast_addzone((ZIa), (ZIparent));
		if ((ZIz) == NULL) {
			perror("ast_addzone");
			goto ZL1;
		}
	
#line 2249 "src/lx/parser.c"
		}
		/* END OF ACTION: make-zone */
		/* BEGINNING OF ACTION: no-exit */
		{
#line 416 "src/lx/parser.act"

		(ZIexit) = NULL;
	
#line 2258 "src/lx/parser.c"
		}
		/* END OF ACTION: no-exit */
		/* BEGINNING OF ACTION: set-globalzone */
		{
#line 405 "src/lx/parser.act"

		assert((ZIa) != NULL);
		assert((ZIz) != NULL);

		(ZIa)->global = (ZIz);
	
#line 2270 "src/lx/parser.c"
		}
		/* END OF ACTION: set-globalzone */
		p_list_Hof_Hthings (lex_state, act_state, ZIa, ZIz, ZIexit);
		/* BEGINNING OF INLINE: 137 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case (TOK_EOF):
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: err-expected-eof */
				{
#line 573 "src/lx/parser.act"

		err_expected(lex_state, "EOF");
	
#line 2298 "src/lx/parser.c"
				}
				/* END OF ACTION: err-expected-eof */
			}
		ZL2:;
		}
		/* END OF INLINE: 137 */
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: make-ast */
		{
#line 344 "src/lx/parser.act"

		(ZIa) = ast_new();
		if ((ZIa) == NULL) {
			perror("ast_new");
			goto ZL4;
		}
	
#line 2319 "src/lx/parser.c"
		}
		/* END OF ACTION: make-ast */
		/* BEGINNING OF ACTION: err-syntax */
		{
#line 541 "src/lx/parser.act"

		err(lex_state, "Syntax error");
		exit(EXIT_FAILURE);
	
#line 2329 "src/lx/parser.c"
		}
		/* END OF ACTION: err-syntax */
	}
	goto ZL0;
ZL4:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOa = ZIa;
}

static void
p_103(lex_state lex_state, act_state act_state, string *ZOt)
{
	string ZIt;

	switch (CURRENT_TERMINAL) {
	case (TOK_MAP):
		{
			/* BEGINNING OF INLINE: 104 */
			{
				{
					switch (CURRENT_TERMINAL) {
					case (TOK_MAP):
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: err-expected-map */
					{
#line 549 "src/lx/parser.act"

		err_expected(lex_state, "'->'");
	
#line 2369 "src/lx/parser.c"
					}
					/* END OF ACTION: err-expected-map */
				}
			ZL2:;
			}
			/* END OF INLINE: 104 */
			switch (CURRENT_TERMINAL) {
			case (TOK_TOKEN):
				/* BEGINNING OF EXTRACT: TOKEN */
				{
#line 150 "src/lx/parser.act"

		/* TODO: submatch addressing */
		ZIt = xstrdup(lex_state->buf.a + 1); /* +1 for '$' prefix */
		if (ZIt == NULL) {
			perror("xstrdup");
			exit(EXIT_FAILURE);
		}
	
#line 2389 "src/lx/parser.c"
				}
				/* END OF EXTRACT: TOKEN */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: no-token */
			{
#line 412 "src/lx/parser.act"

		(ZIt) = NULL;
	
#line 2407 "src/lx/parser.c"
			}
			/* END OF ACTION: no-token */
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
p_expr_C_Cinfix_Hexpr_C_Ccat_Hexpr(lex_state lex_state, act_state act_state, zone ZIz, fsm *ZOq)
{
	fsm ZIq;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		fsm ZI168;

		p_expr_C_Cinfix_Hexpr_C_Cdot_Hexpr (lex_state, act_state, ZIz, &ZI168);
		p_170 (lex_state, act_state, &ZIz, &ZI168, &ZIq);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_expr_C_Cinfix_Hexpr_C_Calt_Hexpr(lex_state lex_state, act_state act_state, zone ZI147, fsm *ZO150)
{
	fsm ZI150;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		fsm ZIq;
		zone ZI149;

		p_expr_C_Cinfix_Hexpr_C_Csub_Hexpr (lex_state, act_state, ZI147, &ZIq);
		p_151 (lex_state, act_state, ZI147, ZIq, &ZI149, &ZI150);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZO150 = ZI150;
}

static void
p_expr_C_Cinfix_Hexpr_C_Cdot_Hexpr(lex_state lex_state, act_state act_state, zone ZIz, fsm *ZOq)
{
	fsm ZIq;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		fsm ZI171;

		p_expr_C_Cprefix_Hexpr (lex_state, act_state, ZIz, &ZI171);
		p_173 (lex_state, act_state, &ZIz, &ZI171, &ZIq);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_expr_C_Cinfix_Hexpr_C_Csub_Hexpr(lex_state lex_state, act_state act_state, zone ZIz, fsm *ZOq)
{
	fsm ZIq;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		fsm ZI165;

		p_expr_C_Cinfix_Hexpr_C_Ccat_Hexpr (lex_state, act_state, ZIz, &ZI165);
		p_167 (lex_state, act_state, &ZIz, &ZI165, &ZIq);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
p_125(lex_state lex_state, act_state act_state)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case (TOK_SEMI):
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: err-expected-semi */
		{
#line 557 "src/lx/parser.act"

		err_expected(lex_state, "';'");
	
#line 2552 "src/lx/parser.c"
		}
		/* END OF ACTION: err-expected-semi */
	}
}

/* BEGINNING OF TRAILER */

#line 626 "src/lx/parser.act"


	struct ast *lx_parse(FILE *f) {
		struct act_state act_state_s;
		struct act_state *act_state;
		struct lex_state lex_state_s;
		struct lex_state *lex_state;
		struct ast *ast;
		struct lx *lx;

		assert(f != NULL);

		lex_state = &lex_state_s;

		lex_state->p = lex_state->a;

		lx = &lex_state->lx;

		lx_init(lx);

		lx->lgetc  = lx_fgetc;
		lx->opaque = f;

		lex_state->buf.a   = NULL;
		lex_state->buf.len = 0;

		lx->buf   = &lex_state->buf;
		lx->push  = lx_dynpush;
		lx->pop   = lx_dynpop;
		lx->clear = lx_dynclear;
		lx->free  = lx_dynfree;

		/* This is a workaround for ADVANCE_LEXER assuming a pointer */
		act_state = &act_state_s;

		ADVANCE_LEXER;	/* XXX: what if the first token is unrecognised? */
		p_lx(lex_state, act_state, &ast);

		assert(ast != NULL);

		return ast;
	}

#line 2604 "src/lx/parser.c"

/* END OF FILE */
