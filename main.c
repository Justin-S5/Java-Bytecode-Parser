#include <stdio.h>
#include "ReadFile/classfile.h"

#define PATH "/Users/justinschaffner/Desktop/Coding/C Projects/Java_Bytecode_Parser/Main.class"

int main() {
    struct ClassFile *class_file = parse(PATH);
    printClassFile(class_file);
    freeClassFile(class_file);
    return 0;
}
