#include "CA.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RULESET_SIZE 8

Rule_t *CA_CreateRuleset()
{
    Rule_t *rules = malloc(RULESET_SIZE * sizeof(Rule_t));
    for (uint8_t i = 0; i < RULESET_SIZE; i++)
    {
        uint8_t k = i;
        rules[i].prevState = k & 1;
        k = k >> 1;
        rules[i].state = k & 1;
        k = k >> 1;
        rules[i].nextState = k & 1;
    }
    return rules;
}

void CA_DeleteRuleset(Rule_t *rules)
{
    free(rules);
}
