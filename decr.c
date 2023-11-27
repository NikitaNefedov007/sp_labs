#include <stdio.h>
#include <stdlib.h>

struct product {
    unsigned char name[32];
    int length; t
    int width;  
    int height;  
};

union item_bytes {
    struct product prdct;
    unsigned char bytes_arr[sizeof(struct product)];
};

unsigned char decrypting(unsigned char byte) {
    return byte + 10;
}

void deserializing(unsigned char* before, unsigned char* after,
                   unsigned char (*decoding)(unsigned char), int size) {
    for (int i = 0; i < size; i++) {
        before[i] = decoding(after[i]);
    }
}

int main() {
    union item_bytes *pointer;
    pointer = malloc(sizeof(struct product));

    if (pointer == NULL) {
        perror("Memory allocation error");
        return 1;
    }

    union item_bytes cur_bts = *pointer;

    char filename[256];
    printf("Enter the file name for reading (maximum 256 characters): ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening the file");
        free(pointer); // free memory
        return 1;
    }

    fread(cur_bts.bytes_arr, sizeof(unsigned char), sizeof(struct product), file);
    fclose(file);

    deserializing(cur_bts.bytes_arr, cur_bts.bytes_arr, decrypting, sizeof(struct product));

    printf("Product name: %s\n", cur_bts.prdct.name);
    printf("Length: %d\n", cur_bts.prdct.length);  
    printf("Width: %d\n", cur_bts.prdct.width);    
    printf("Height: %d\n", cur_bts.prdct.height);  
    free(pointer); // free memory

    return 0;
}
