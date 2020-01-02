/*
 * Copyright 2008-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>

#include <fsm/fsm.h>

#include <adt/set.h>
#include <adt/stateset.h>
#include <adt/edgeset.h>

#include "internal.h"

fsm_state_t
fsm_findmode(const struct fsm *fsm, fsm_state_t state, unsigned int *freq)
{
	struct edge_iter it;
	struct fsm_edge *e;

	struct {
		fsm_state_t state;
		unsigned int freq;
	} mode;

	mode.freq = 1;

	assert(fsm != NULL);
	assert(state < fsm->statecount);

	for (e = edge_set_first(fsm->states[state].edges, &it); e != NULL; e = edge_set_next(&it)) {
		struct edge_iter kt = it;
		struct fsm_edge *c;
		unsigned int curr;

		curr = 1; /* including ourself */

		/*
		 * Count the remaining edes which have the same destination.
		 */
		for (c = edge_set_next(&kt); c != NULL; c = edge_set_next(&kt)) {
			if (c->state == e->state) {
				curr++;
			}
		}

		if (curr > mode.freq) {
			mode.freq  = curr;
			mode.state = e->state;
		}
	}

	if (freq != NULL) {
		*freq = mode.freq;
	}

	assert(mode.freq >= 1);

	return mode.state;
}

