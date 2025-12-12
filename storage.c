#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 512

int storage_load(const char *filename, Student *students, int max_count) {
    if (!filename || !students || max_count <= 0) return -1;
    
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    
    char line[MAX_LINE_LEN];
    int count = 0;
    int line_num = 0;
    
    while (fgets(line, sizeof(line), f) && count < max_count) {
        line_num++;
        
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        if (line[0] == '\0' || line[0] == '#') continue;
        
        Student s;
        if (student_parse(line, &s)) {
            students[count++] = s;
        } else {
            fprintf(stderr, "Warning: Skipping malformed line %d\n", line_num);
        }
    }
    
    fclose(f);
    return count;
}

int storage_save(const char *filename, const Student *students, int count) {
    if (!filename || !students || count < 0) return 0;
    
    char temp_name[256];
    snprintf(temp_name, sizeof(temp_name), "%s.tmp", filename);
    
    FILE *f = fopen(temp_name, "w");
    if (!f) {
        perror("Failed to open temp file");
        return 0;
    }
    
    char buf[MAX_LINE_LEN];
    for (int i = 0; i < count; i++) {
        if (!student_format(&students[i], buf, sizeof(buf))) {
            fprintf(stderr, "Error formatting student %d\n", i);
            fclose(f);
            remove(temp_name);
            return 0;
        }
        
        if (fputs(buf, f) == EOF) {
            perror("Write failed");
            fclose(f);
            remove(temp_name);
            return 0;
        }
    }
    
    if (fflush(f) != 0) {
        perror("Flush failed");
        fclose(f);
        remove(temp_name);
        return 0;
    }
    
    fclose(f);
    
    if (rename(temp_name, filename) != 0) {
        perror("Rename failed");
        remove(temp_name);
        return 0;
    }
    
    return 1;
}
