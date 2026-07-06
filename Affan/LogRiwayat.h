#ifndef LOGRIWAYAT_H
#define LOGRIWAYAT_H

#include <string>

void displaySearchHistory();
void pushSearchHistory(std::string keyword);
void popSearchHistory();
void redoSearchHistory();
void menuLogRiwayat();
void clearStack();

#endif
