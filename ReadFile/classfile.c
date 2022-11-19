#include "classfile.h"

// TODO Fix UTF8.bytes wiping values
//! DEBUG
int debug_bytes(char* path) {
    int line;
    FILE *file = fopen(path, "rb"); // Open file
    if (file == NULL) {
        printf("File not found!");
        return -1; // File is not found, exit
    }

    while ((line = fgetc(file)) != EOF) {
        printf("%02x\n", line);
    }
    return 0;
}

/*!
 * @brief Combines four bytes into a 32-bit integer.
 * @param byte1 byte 1
 * @param byte2 byte 2
 * @param byte3 byte 3
 * @param byte4 byte 4
 * @return ui32 32-bit integer
 */
static ui32 parseU4(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
    ui32 magic_byte1 = (byte1 << 8) | byte2;  // 0xCAFE
    ui32 magic_byte2 = (byte3 << 8) | byte4;  // 0xBABE
    return (magic_byte1 << 16) | magic_byte2; // 0xCAFEBABE
}

/*!
 * @brief Combines two bytes into a single ui32.
 * @param byte1 first byte
 * @param byte2 second byte
 * @return ui32 32-bit integer
 */
static ui32 parseU2(uint8_t byte1, uint8_t byte2) {
    return (byte1 << 8) | byte2;
}

/*!
 * @brief Print ClassFile contents.
 * @param class_file class file
 * @return void
 */
void printClassFile(struct ClassFile* class_file) {
    printf("Class Items:\n");
    printf(" | Magic: %02x\n", class_file->magic);
    printf(" | Minor Version: %d\n", class_file->minorVersion);
    printf(" | Major Version: %d\n", class_file->majorVersion);
    printf(" | Constant Pool Count: %d\n", class_file->constantPoolCount);
    for (int i = 0; i < class_file->constantPoolCount - 1; i++) {
        uint8_t tag = class_file->constantPoolInfo[i]->tag;
        if (tag == CONSTANT_Methodref) {
            printf(" | Tag: %d | Class Index: %d | Name and Type Index: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_Methodref_info.class_index, class_file->constantPoolInfo[i]->info.CONSTANT_Methodref_info.name_and_type_index);
        } else if (tag == CONSTANT_Class) {
            printf(" | Tag: %d | Name Index: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_Class_info.name_index);
        } else if (tag == CONSTANT_NameAndType) {
            printf(" | Tag: %d | Name Index: %d | Descriptor Index: %d\n", tag,
                   class_file->constantPoolInfo[i]->info.CONSTANT_NameAndType_info.name_index,
                   class_file->constantPoolInfo[i]->info.CONSTANT_NameAndType_info.descriptor_index);
        } else if (tag == CONSTANT_Utf8) {
            printf(" | Tag: %d | Length: %d | Bytes: %s\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_Utf8_info.length, class_file->constantPoolInfo[i]->info.CONSTANT_Utf8_info.bytes);
        } else if (tag == CONSTANT_String) {
            printf(" | Tag: %d | String Index: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_String_info.string_index);
        } else if (tag == CONSTANT_Fieldref) {
            printf(" | Tag: %d | Class Index: %d | Name and Type Index: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_Fieldref_info.class_index, class_file->constantPoolInfo[i]->info.CONSTANT_Fieldref_info.name_and_type_index);
        } else if (tag == CONSTANT_Integer) {
            printf(" | Tag: %d | Bytes: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_Integer_info.bytes);
        } else if (tag == CONSTANT_Float) {
            printf(" | Tag: %d | Bytes: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_Float_info.bytes);
        } else if (tag == CONSTANT_Long) {
            printf(" | Tag: %d | High Bytes: %d | Low Bytes: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_Long_info.high_bytes, class_file->constantPoolInfo[i]->info.CONSTANT_Long_info.low_bytes);
        } else if (tag == CONSTANT_Double) {
            printf(" | Tag: %d | High Bytes: %d | Low Bytes: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_Double_info.high_bytes, class_file->constantPoolInfo[i]->info.CONSTANT_Double_info.low_bytes);
        } else if (tag == CONSTANT_InterfaceMethodref) {
            printf(" | Tag: %d | Class Index: %d | Name and Type Index: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_InterfaceMethodref_info.class_index, class_file->constantPoolInfo[i]->info.CONSTANT_InterfaceMethodref_info.name_and_type_index);
        } else if (tag == CONSTANT_MethodHandle) {
            printf(" | Tag: %d | Reference Kind: %d | Reference Index: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_MethodHandle_info.reference_kind, class_file->constantPoolInfo[i]->info.CONSTANT_MethodHandle_info.reference_index);
        } else if (tag == CONSTANT_MethodType) {
            printf(" | Tag: %d | Descriptor Index: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_MethodType_info.descriptor_index);
        } else if (tag == CONSTANT_InvokeDynamic) {
            printf(" | Tag: %d | Bootstrap Method Attr Index: %d | Name and Type Index: %d\n", tag, class_file->constantPoolInfo[i]->info.CONSTANT_InvokeDynamic_info.bootstrap_method_attr_index, class_file->constantPoolInfo[i]->info.CONSTANT_InvokeDynamic_info.name_and_type_index);
        }
    }
}

/*!
 * @brief Parse a Java class file.
 * @param path path to class file
 * @return ClassFile struct
 */
struct ClassFile* parse(char *path) {
    struct ClassFile* class_file = malloc(sizeof(struct ClassFile)); // Allocate memory for class file
    uint8_t *buffer = malloc(sizeof(uint8_t)); // Allocate memory for buffer
    FILE *file = fopen(path, "rb"); // Open file
    if (file == NULL) {
        printf("File not found!");
        return NULL; // File is not found, exit
    }

    fread(buffer, sizeof (uint8_t), 4, file); // Magic
    class_file->magic = parseU4(buffer[0], buffer[1], buffer[2], buffer[3]);
    fread(buffer, sizeof (uint8_t), 2, file); // Minor Version
    class_file->minorVersion = parseU2(buffer[0], buffer[1]);
    fread(buffer, sizeof (uint8_t), 2, file); // Major Version
    class_file->majorVersion = parseU2(buffer[0], buffer[1]);
    fread(buffer, sizeof (uint8_t), 2, file); // Constant Pool Count
    class_file->constantPoolCount = parseU2(buffer[0], buffer[1]);
    class_file->constantPoolInfo = malloc(sizeof(struct ConstantPoolInfo) * class_file->constantPoolCount - 1);
    // Constant Pool
    for (int i = 0; i < class_file->constantPoolCount - 1; i++) {
        fread(buffer, sizeof (uint8_t), 1, file); // Tag
        uint8_t tag = buffer[0];
        class_file->constantPoolInfo[i]->tag = tag;
        if (tag == CONSTANT_Methodref) {
            fread(buffer, sizeof (uint8_t), 2, file); // Class Index
            class_file->constantPoolInfo[i]->info.CONSTANT_Methodref_info.class_index = parseU2(buffer[0], buffer[1]);
            fread(buffer, sizeof (uint8_t), 2, file); // Name and Type Index
            class_file->constantPoolInfo[i]->info.CONSTANT_Methodref_info.name_and_type_index = parseU2(buffer[0],buffer[1]);
        } else if (tag == CONSTANT_Class) {
            fread(buffer, sizeof (uint8_t), 2, file); // Name Index
            class_file->constantPoolInfo[i]->info.CONSTANT_Class_info.name_index = parseU2(buffer[0], buffer[1]);
        } else if (tag == CONSTANT_NameAndType) {
            fread(buffer, sizeof(uint8_t), 2, file); // Name Index
            class_file->constantPoolInfo[i]->info.CONSTANT_NameAndType_info.name_index = parseU2(buffer[0], buffer[1]);
            fread(buffer, sizeof(uint8_t), 2, file); // Descriptor Index
            class_file->constantPoolInfo[i]->info.CONSTANT_NameAndType_info.descriptor_index = parseU2(buffer[0],buffer[1]);
        } else if (tag == CONSTANT_Utf8) {
            class_file->constantPoolInfo[i]->info.CONSTANT_Utf8_info.bytes = malloc(sizeof(uint8_t));
            fread(buffer, sizeof(uint8_t), 2, file);//
            class_file->constantPoolInfo[i]->info.CONSTANT_Utf8_info.length = parseU2(buffer[0], buffer[1]);
            fread(buffer, sizeof(uint8_t), class_file->constantPoolInfo[i]->info.CONSTANT_Utf8_info.length, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_Utf8_info.bytes = buffer;
            printf("%s\n", class_file->constantPoolInfo[i]->info.CONSTANT_Utf8_info.bytes);
        } else if (tag == CONSTANT_String) {
            fread(buffer, sizeof(uint8_t), 2, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_String_info.string_index = parseU2(buffer[0], buffer[1]);
        } else if (tag == CONSTANT_Fieldref) {
            fread(buffer, sizeof(uint8_t), 2, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_Fieldref_info.class_index = parseU2(buffer[0], buffer[1]);
            fread(buffer, sizeof(uint8_t), 2, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_Fieldref_info.name_and_type_index = parseU2(buffer[0],buffer[1]);
        } else if (tag == CONSTANT_Integer) {
            fread(buffer, sizeof(uint8_t), 4, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_Integer_info.bytes = parseU4(buffer[0], buffer[1], buffer[2], buffer[3]);
        } else if (tag == CONSTANT_Float) {
            fread(buffer, sizeof(uint8_t), 4, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_Float_info.bytes = parseU4(buffer[0], buffer[1], buffer[2], buffer[3]);
        } else if (tag == CONSTANT_Long) {
            fread(buffer, sizeof(uint8_t), 4, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_Long_info.low_bytes = parseU4(buffer[0], buffer[1], buffer[2], buffer[3]);
            fread(buffer, sizeof(uint8_t), 4, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_Long_info.high_bytes = parseU4(buffer[0], buffer[1], buffer[2], buffer[3]);
            fread(buffer, sizeof(uint8_t), 4, file); // Next entry is invalid
        } else if (tag == CONSTANT_Double) {
            fread(buffer, sizeof(uint8_t), 4, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_Double_info.low_bytes = parseU4(buffer[0], buffer[1], buffer[2], buffer[3]);
            fread(buffer, sizeof(uint8_t), 4, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_Double_info.high_bytes = parseU4(buffer[0], buffer[1], buffer[2], buffer[3]);
            fread(buffer, sizeof(uint8_t), 4, file); // Next entry is invalid
        } else if (tag == CONSTANT_MethodHandle) {
            fread(buffer, sizeof(uint8_t), 1, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_MethodHandle_info.reference_index = buffer[0];
            fread(buffer, sizeof(uint8_t), 2, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_MethodHandle_info.reference_index = parseU2(buffer[0], buffer[1]);
        } else if (tag == CONSTANT_MethodType) {
            fread(buffer, sizeof(uint8_t), 2, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_MethodType_info.descriptor_index = parseU2(buffer[0], buffer[1]);
        } else if (tag == CONSTANT_InterfaceMethodref) {
            fread(buffer, sizeof(uint8_t), 2, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_InterfaceMethodref_info.class_index = parseU2(buffer[0], buffer[1]);
            fread(buffer, sizeof(uint8_t), 2, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_InterfaceMethodref_info.name_and_type_index = parseU2(buffer[0], buffer[1]);
        } else if (tag == CONSTANT_InvokeDynamic) {
            fread(buffer, sizeof(uint8_t), 2, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_InvokeDynamic_info.bootstrap_method_attr_index = parseU2(buffer[0], buffer[1]);
            fread(buffer, sizeof(uint8_t), 2, file);
            class_file->constantPoolInfo[i]->info.CONSTANT_InvokeDynamic_info.name_and_type_index = parseU2(buffer[0], buffer[1]);
        } else return NULL;
        memset(buffer, 0, sizeof(buffer) * 5); // Clear buffer, I don't know why but "* 5" makes it work
    }



    free(buffer);
    return class_file;
}

/*!
 * @brief free a ClassFile struct and all its members.
 * @param class_file ClassFile struct
 * @return void
 */
void freeClassFile(struct ClassFile* class_file) {
    free(class_file->constantPoolInfo);
    free(class_file->interfaces);
    free(class_file->fields);
    free(class_file->methods);
    free(class_file->attributes);
    free(class_file);
}
