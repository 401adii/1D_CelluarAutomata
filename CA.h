#ifndef CA_H
#define CA_H

#include "CellRow.h"
#include "Rule.h"

Rule_t *CA_CreateRuleset(void);
void CA_UpdateRulesetOutcome(Rule_t *rules, uint8_t ruleNum);
void CA_Run(CellRow_t *row1, CellRow_t *row2, Rule_t *rules);
void CA_Loop(CellRow_t *row1, CellRow_t *row2, Rule_t *rules);
void CA_DeleteRuleset(Rule_t *rules);

#endif
