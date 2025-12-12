#ifndef STORAGE_H
#define STORAGE_H

#include "student.h"

int storage_load(const char *filename, Student *students, int max_count);
int storage_save(const char *filename, const Student *students, int count);

#endif /* STORAGE_H */
