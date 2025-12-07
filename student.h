#ifndef STUDENT_H
#define STUDENT_H

#include <stddef.h>

#define MAX_NAME_LEN 64 //64 characters max
#define MAX_STUDENTS 1000 //1000 students max

typedef struct {
	int id;
	char name[MAX_NAME_LEN];
	double score1;
	double score2;
	double score3;
}Student;//constructor

//Prototypes
// compute average score for a student
double student_average(const Student *s);
// validate student data
int student_is_valid(const Student *s);
// parse a student from a CSV
int student_parse(const char *line, Student *s);
// format a student as a CSV
int student_format(const Student *s, char *buf, size_t size);
// print student
void student_print(const Student *s);

#endif
