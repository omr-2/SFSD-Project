#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORD_SIZE 100

typedef struct {
    int record_ID;
    char content[MAX_RECORD_SIZE];
} Record;

typedef struct {
    int is_empty;
    char file_name[50];
    int next_block;
    int num_records;
    Record record_data;
} Block;

typedef struct {
    char name[50];
    int total_records;
    int global_organ;
    int internal_organ;
    Block *blocks[MAX_RECORD_SIZE];
} File;

typedef struct {
    char meta_file_name[50];
    int block_count;
    int record_count;
    int first_block_addr;
    int global_mode;
    int internal_mode;
} MetaInfo;

Block *disk_blocks = NULL;

void initialize_disk(int block_num, int block_factor) {
    disk_blocks = (Block *)malloc(block_num * sizeof(Block));
    if (disk_blocks == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }

    for (int i = 0; i < block_num; i++) {
        disk_blocks[i].is_empty = 1;
        disk_blocks[i].next_block = -1;
    }
}

void create_meta_info(File *file_obj, MetaInfo *meta_info) {
    strcpy(meta_info->meta_file_name, file_obj->name);
    meta_info->block_count = file_obj->total_records;
    meta_info->record_count = file_obj->total_records;
    meta_info->first_block_addr = (file_obj->blocks[0] != NULL) ? file_obj->blocks[0] - disk_blocks : -1;
    meta_info->global_mode = file_obj->global_organ;
    meta_info->internal_mode = file_obj->internal_organ;
}
int read_meta_info(FILE *file_obj,int n1){
   rewind(file_obj);
   MetaInfo car;
   switch(n1){
   case 2:
       return car.block_count;
       break;
   case 3:
        return car.record_count;
        break;
   case 4:
        return car.first_block_addr;
        break;
   case 5:
        return car.global_mode;
        break;
   case 6:
        return car.internal_mode;
        break;
   default:
         printf("Invalid option.\n");
         break;
   }
}

void display_meta_info(MetaInfo *meta_info) {
    printf("File Name: %s\n", meta_info->meta_file_name);
    printf("File Size (blocks): %d\n", meta_info->block_count);
    printf("File Size (records): %d\n", meta_info->record_count);
    printf("Address of the first block: %d\n", meta_info->first_block_addr);
    printf("Global Organization Mode: %d\n", meta_info->global_mode);
    printf("Internal Organization Mode: %d\n", meta_info->internal_mode);
}

void create_file(File *file_obj) {
    printf("Enter the file name: ");
    scanf("%s", file_obj->name);

    printf("Enter the number of records: ");
    scanf("%d", &file_obj->total_records);
    for (int i = 0; i < file_obj->total_records; i++) {
        file_obj->blocks[i] = NULL;
    }
    printf("Choose global organization mode (0 for Contiguous, 1 for Chained): ");
    scanf("%d", &file_obj->global_organ);

    printf("Choose internal organization mode (0 for Unsorted, 1 for Sorted): ");
    scanf("%d", &file_obj->internal_organ);
}

void insert_record(File *file_obj, Record new_record) {
    for (int i = 0; i < MAX_RECORD_SIZE; i++) {
        if (disk_blocks[i].is_empty) {
            disk_blocks[i].is_empty = 0;
            disk_blocks[i].record_data = new_record;
            strcpy(disk_blocks[i].file_name, file_obj->name);
            file_obj->blocks[i] = &disk_blocks[i];
            break;
        }
    }
}

int search_record(File *file_obj, int record_ID) {
    for (int i = 0; i < file_obj->total_records; i++) {
        if (file_obj->blocks[i] != NULL && file_obj->blocks[i]->record_data.record_ID == record_ID) {
            printf("Record is located in block %d\n", i);
            return i;
        }
    }
    printf("Record not found.\n");
    return -1;
}

void edit_record(File *file_obj, int record_ID, char *new_content) {
    int block_index = search_record(file_obj, record_ID);
    if (block_index != -1) {
        strcpy(file_obj->blocks[block_index]->record_data.content, new_content);
        printf("Record with ID %d has been successfully updated.\n", record_ID);
    }
}

void delete_record(File *file_obj, int record_ID) {
    int block_index = search_record(file_obj, record_ID);
    if (block_index != -1) {
        file_obj->blocks[block_index]->is_empty = 1;
        file_obj->blocks[block_index] = NULL;
        printf("Record with ID %d deleted.\n", record_ID);
    }
}

void sort_file(File *file_obj) {
    if (file_obj->internal_organ == 1) {
        for (int i = 0; i < file_obj->total_records - 1; i++) {
            for (int j = i + 1; j < file_obj->total_records; j++) {
                if (file_obj->blocks[i] != NULL && file_obj->blocks[j] != NULL &&
                    file_obj->blocks[i]->record_data.record_ID > file_obj->blocks[j]->record_data.record_ID) {
                    Record temp = file_obj->blocks[i]->record_data;
                    file_obj->blocks[i]->record_data = file_obj->blocks[j]->record_data;
                    file_obj->blocks[j]->record_data = temp;
                }
            }
        }
    }
}

void defragment_file(File *file_obj) {
    int index = 0;
    for (int i = 0; i < file_obj->total_records; i++) {
        if (file_obj->blocks[i] != NULL) {
            if (index != i) {
                file_obj->blocks[index] = file_obj->blocks[i];
                file_obj->blocks[i] = NULL;
            }
            index++;
        }
    }
}

void compact_memory() {
    int compact_index = 0;
    for (int i = 0; i < MAX_RECORD_SIZE; i++) {
        if (!disk_blocks[i].is_empty) {
            if (compact_index != i) {
                disk_blocks[compact_index] = disk_blocks[i];
                disk_blocks[i].is_empty = 1;
            }
            compact_index++;
        }
    }
    printf("Memory compacted successfully.\n");
}

void delete_file(File *file_obj) {
    for (int i = 0; i < file_obj->total_records; i++) {
        if (file_obj->blocks[i] != NULL) {
            file_obj->blocks[i]->is_empty = 1;
            file_obj->blocks[i] = NULL;
        }
    }
    printf("File %s deleted.\n", file_obj->name);
}

void display_file(File *file_obj) {
    printf("File Name: %s\n", file_obj->name);
    printf("Total Records: %d\n", file_obj->total_records);
    for (int i = 0; i < file_obj->total_records; i++) {
        if (file_obj->blocks[i] != NULL) {
            printf("ID: %d, Content: %s\n", file_obj->blocks[i]->record_data.record_ID, file_obj->blocks[i]->record_data.content);
        }
    }
}

void display_disk_status() {
    printf("\nDisk Status:\n");
    for (int i = 0; i < MAX_RECORD_SIZE; i++) {
        printf("---------------------\n");
        printf("| ");
        if (disk_blocks[i].is_empty) {
            printf("Empty          ");
        } else {
            printf("%-8s %2d records", disk_blocks[i].file_name, disk_blocks[i].num_records);
        }
        printf(" |\n");
        printf("---------------------\n");
    }
}

int main() {
    File main_file;
    MetaInfo meta_info;
    int user_choice, record_ID;
    char new_content[MAX_RECORD_SIZE];
    Record new_record;
    int total_blocks, block_factor;

    printf("Enter the number of available blocks on the disk: ");
    scanf("%d", &total_blocks);
    printf("Enter the maximum block size (blocking factor): ");
    scanf("%d", &block_factor);

    initialize_disk(total_blocks, block_factor);

    while (1) {
        printf("\n*********************   Menu:    ******************************\n");
        printf("1. Create a file\n");
        printf("2. Insert a record\n");
        printf("3. Search for a record by ID\n");
        printf("4. Modify a record\n");
        printf("5. Sort records\n");
        printf("6. Delete a record\n");
        printf("7. Display the file\n");
        printf("8. Defragment the file\n");
        printf("9. Compact memory\n");
        printf("10. Clear memory\n");
        printf("11. Rename a file\n");
        printf("12. Delete a file\n");
        printf("13. Display metadata\n");
        printf("14. Display disk status\n");
        printf("15. Exit\n");
        printf("*******************************************************************\n");
        printf("Choose an option: ");
        scanf("%d", &user_choice);

        switch (user_choice) {
            case 1:
                create_file(&main_file);
                create_meta_info(&main_file, &meta_info);
                break;
            case 2:
                printf("Enter the record ID: ");
                scanf("%d", &new_record.record_ID);
                printf("Enter the record content: ");
                getchar();
                fgets(new_record.content, MAX_RECORD_SIZE, stdin);
                new_record.content[strcspn(new_record.content, "\n")] = 0;
                insert_record(&main_file, new_record);
                create_meta_info(&main_file, &meta_info);
                break;
            case 3:
                printf("Enter the record ID to search: ");
                scanf("%d", &record_ID);
                search_record(&main_file, record_ID);
                break;
            case 4:
                printf("Enter the record ID to modify: ");
                scanf("%d", &record_ID);
                printf("Enter the new content: ");
                getchar();
                fgets(new_content, MAX_RECORD_SIZE, stdin);
                new_content[strcspn(new_content, "\n")] = 0;
                edit_record(&main_file, record_ID, new_content);
                break;
            case 5:
                sort_file(&main_file);
                printf("File sorted successfully.\n");
                break;
            case 6:
                printf("Enter the record ID to delete: ");
                scanf("%d", &record_ID);
                delete_record(&main_file, record_ID);
                break;
            case 7:
                display_file(&main_file);
                break;
            case 8:
                defragment_file(&main_file);
                break;
            case 9:
                compact_memory();
                break;
            case 10:
                for (int i = 0; i < total_blocks; i++) {
                    disk_blocks[i].is_empty = 1;
                }
                printf("Disk memory cleared.\n");
                break;
            case 11:
                printf("Enter the new name for the file: ");
                getchar();
                fgets(main_file.name, 50, stdin);
                main_file.name[strcspn(main_file.name, "\n")] = 0;
                printf("File renamed successfully.\n");
                break;
            case 12:
                delete_file(&main_file);
                break;
            case 13:
                display_meta_info(&meta_info);
                break;
            case 14:
                display_disk_status();
                break;
            case 15:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
}
