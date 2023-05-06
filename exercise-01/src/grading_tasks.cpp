#include "grading_tasks.h"

#include <stdio.h>

#include <fstream>

#include "grading_table.cpp"
#include "grading_table.h"

void IteratingTaskAgent::performTask() {
    int *result = visitAll();
    for (int i = 0; i < CONST_MAX_EXPECTED_RESULTS; i++) {
        printf("%d\n", result[i]);
    }
}

int *IteratingTaskAgent::visitAll() {
    int *result = new int[CONST_MAX_EXPECTED_RESULTS];
    for (int i = 0; i < CONST_MAX_EXPECTED_RESULTS; i++) {
        result[i] = 0;
    }

    int i = 0;
    for (GradingTableEntry el : *table) {
        if (visit(&el) != 0) {
            result[i++] = visit(&el);
        }
    }

    return result;
}

void ReducingTaskAgent::performTask() {
    printf("%d", reduceAll());
}

int ReducingTaskAgent::reduceAll() {
    int result = 0;
    for (GradingTableEntry el : *table) {
        result = reduce(&el, result);
    }

    return result;
}

int TaskA::visit(GradingTableEntry *current) {
    return current->points;
}

int TaskB::visit(GradingTableEntry *current) {
    return current->points < 10 ? current->mat_no : 0;
}

int TaskC::reduce(GradingTableEntry *current, int value) {
    return value + 1;
}

int TaskD::reduce(GradingTableEntry *current, int value) {
    return current->points > value ? current->points : value;
}

int TaskE::reduce(GradingTableEntry *current, int value) {
    return current->series == 3 ? value + current->points : value;
}
