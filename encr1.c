#include <stdio.h>
#include <stdlib.h>

struct product {
    unsigned char name[32];
    int length;  
    int width;  
    int height; 
};

union item_bytes {
    struct product prdct;
    unsigned char bytes_arr[sizeof(struct product)];
};

unsigned char encrypting(unsigned char cur_byte) {
    return cur_byte - 10;
}

void serializing(unsigned char* before, unsigned char* after,
                 unsigned char (*encoding)(unsigned char), int size) {
    for (int i = 0; i < size; i++)
        after[i] = encoding(before[i]);
}

int main() {
    struct product cur_prdct;

    printf("Enter the product name (maximum 32 characters): ");
    scanf("%s", cur_prdct.name);

    printf("Enter the length (integer): ");
    scanf("%d", &cur_prdct.length);  

    printf("Enter the width (integer): ");
    scanf("%d", &cur_prdct.width); 

    printf("Enter the height (integer): ");
    scanf("%d", &cur_prdct.height); d

    char filename[256];
    printf("Enter the file name for saving (maximum 256 characters): ");
    scanf("%s", filename);

    union item_bytes *pointer;
    pointer = malloc(sizeof(cur_prdct));
    if (pointer == NULL) {
        perror("Memory allocation error");
        return 1;
    }

    union item_bytes cur_bts = *pointer;
    serializing((unsigned char*)&cur_prdct, cur_bts.bytes_arr, encrypting, sizeof(cur_prdct));

    FILE *file = fopen(filename, "wb");
    fwrite(cur_bts.bytes_arr, sizeof(unsigned char), sizeof(struct product), file);
    fclose(file);

    free(pointer); 

    return 0;
}
