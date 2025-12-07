#include "student.h"
#include <stdio.h>
#include <string.h> //just in case if needed
#include <ctype.h> //for isspace

//calculates avg for stats.c
double student_average(const Student *s) {
	if (!s) return 0.0;//returns 0 if no student in record

	return (s->score1 + s->score2 + s->score3) / 3.0;
}

//checks for any faulty data in a student. for main.c
int student_is_valid(const Student *s) {
	//defensive checks
	if (!s) return 0;
	if (s->id <= 0) return 0;
	if (s->name[0] == '\0') return 0;
	if (s->score1 < 0.0 || s->score1 > 100.0) return 0;
	if (s->score2 < 0.0 || s->score2 > 100.0) return 0;
	if (s->score3 < 0.0 || s->score3 > 100.0) return 0;
	return 1;//valid if student data get through all checks
}

// parse CSV fields, handling quotes and escapes. Used for student_parse only
static int parse_csv_field(const char **src, char *dst, size_t dst_size) {
	const char *p = *src;
	size_t len = 0;

	// skips leading whitespace
	while (*p && isspace(*p)) p++;

	if (*p == '"') {
		// quoted field
		p++;
		//copies characters until ending " or end of string
		while (*p && *p != '"' && len < dst_size - 1) {
			//skips escape
			if (*p == '\\' && *(p + 1)) {
			p++;
			}

			dst[len++] = *p++;
		}

		if (*p == '"') p++;
	}
	else {
		// unquoted field, like id and scores
		while (*p && *p != ',' && len < dst_size - 1) {
			dst[len++] = *p++;
		}
	}

	//clears dst buffer
	dst[len] = '\0';
	// skips comma
	if (*p == ',') p++;

	//updates pointer to new read position
	*src = p;

	return 1;//success
}

//takes a line of CSV text and fills Student struct. Use for storage.c
int student_parse(const char *line, Student *s) {
	if (!line || !s) return 0;//defensive check

	char buf[256];//local buffer
	const char *p = line;

	// parses id
	if (!parse_csv_field(&p, buf, sizeof(buf))) return 0;
	if (sscanf(buf, "%d", &s->id) != 1) return 0;

	// parses names
	if (!parse_csv_field(&p, s->name, MAX_NAME_LEN)) return 0;

	// parses scores
	if (!parse_csv_field(&p, buf, sizeof(buf))) return 0;
	if (sscanf(buf, "%lf", &s->score1) != 1) return 0;

	if (!parse_csv_field(&p, buf, sizeof(buf))) return 0;
	if (sscanf(buf, "%lf", &s->score2) != 1) return 0;

	if (!parse_csv_field(&p, buf, sizeof(buf))) return 0;
	if (sscanf(buf, "%lf", &s->score3) != 1) return 0;

	return student_is_valid(s);//success
}

//converts Student struct into a comma separated string. Use for storage.c
int student_format(const Student *s, char *buf, size_t size) {
	if (!s || !buf || size == 0) return 0;

	int written = snprintf(buf, size, "%d,\"%s\",%.2f,%.2f,%.2f\n",
				s->id, s->name, s->score1, s->score2, s->score3);

	return written > 0 && (size_t)written < size;
}

//prints student data to the console. Use for main.c
void student_print(const Student *s) {
	if (!s) return;
	printf("ID: %d | Name: %s | Scores: %.2f, %.2f, %.2f | Avg: %.2f\n",
		s->id, s->name, s->score1, s->score2, s->score3, student_average(s));
}
