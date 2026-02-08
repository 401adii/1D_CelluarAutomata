#ifndef CA_H
#define CA_H

#include "Rule.h"

Rule_t *CA_CreateRuleset(void);
void CA_UpdateRulesetOutcome(Rule_t *rules, uint8_t ruleNum);
void CA_DeleteRuleset(Rule_t *rules);

#endif
