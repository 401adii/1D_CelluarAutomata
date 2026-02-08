#ifndef RULE_H
#define RULE_H

#include "Cell.h"
#include <stdint.h>

typedef struct
{
    uint8_t state;
    uint8_t prevState;
    uint8_t nextState;
    uint8_t outcome;
} Rule_t;

typedef enum
{
    RULE_OK = 0,
    RULE_ERROR
} RuleStatus_t;

void Rule_Print(Rule_t rule);
RuleStatus_t Rule_Check(Rule_t *rule, Cell_t *cell);

#endif
