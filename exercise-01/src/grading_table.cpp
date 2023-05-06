#include "grading_table.h"

#include <stdlib.h>

#include <fstream>
#include <iostream>

GradingTable::GradingTable(std::ifstream &fp) {
    g_head = nullptr;
    g_tail = nullptr;

    while (fp.is_open() && !fp.eof()) {
        GradingTableEntry *g_entry = new GradingTableEntry();
        g_entry->next = nullptr;

        fp.read(reinterpret_cast<char *>(&g_entry->mat_no), sizeof(g_entry->mat_no));
        if (fp.eof()) {
            delete g_entry;
            break;
        }
        fp.read(reinterpret_cast<char *>(&g_entry->series), sizeof(g_entry->series));
        fp.read(reinterpret_cast<char *>(&g_entry->points), sizeof(g_entry->points));

        if (g_head == nullptr) {
            g_head = g_tail = g_entry;
        } else {
            g_tail->next = g_entry;
            g_tail = g_entry;
        }
    }
}

GradingTable::~GradingTable() {
    while (g_head) {
        GradingTableEntry *next = g_head->next;
        delete g_head;
        g_head = next;
    }
}
