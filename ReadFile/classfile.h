//
// Created by Justin Schaffner on 10/26/22.
//

#ifndef PRACTICE_CLASSFILE_H
#define PRACTICE_CLASSFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <strings.h>
#include "constantpool.h"

// BaseType Characters
#define JAVA_BOOLEAN                Z
#define JAVA_CHAR                   C
#define JAVA_FLOAT                  F
#define JAVA_DOUBLE                 D
#define JAVA_BYTE                   B
#define JAVA_SHORT                  S
#define JAVA_INT                    I
#define JAVA_LONG                   J
#define JAVA_OBJECT                 Ljava/lang/Object;
#define JAVA_INT_ARRAY              [I
#define JAVA_OBJECT_ARRAY           [Ljava/lang/Object;
#define JAVA_OBJECT_ARRAY_ARRAY     [[Ljava/lang/Object;
// End BaseType Characters

// Access Flags
#define ACC_PUBLIC          0x0001
#define ACC_PRIVATE         0x0002
#define ACC_PROTECTED       0x0004
#define ACC_STATIC          0x0008
#define ACC_FINAL           0x0010
#define ACC_SUPER           0x0020
#define ACC_SYNCHRONIZED    0x0020
#define ACC_VOLATILE        0x0040
#define ACC_BRIDGE          0x0040
#define ACC_TRANSIENT       0x0080
#define ACC_VARARGS         0x0080
#define ACC_NATIVE          0x0100
#define ACC_INTERFACE       0x0200
#define ACC_ABSTRACT        0x0400
#define ACC_STRICT          0x0800
#define ACC_SYNTHETIC       0x1000
#define ACC_ANNOTATION      0x2000
#define ACC_ENUM            0x4000
#define ACC_MANDATED        0x8000
// End Access Flags

// Java Bytecode Instruction Set
#define aaload	        0x32          // 0011 0010
#define aastore	        0x53	      // 0101 0011
#define aconst_null    	0x01	      // 0000 0001
#define aload	        0x19	      // 0001 1001
#define aload_0	        0x2a	      // 0010 1010
#define aload_1	        0x2b	      // 0010 1011
#define aload_2	        0x2c	      // 0010 1100
#define aload_3	        0x2d	      // 0010 1101
#define anewarray       0xbd	      // 1011 1101
#define areturn	        0xb0	      // 1011 0000
#define arraylength	    0xbe	      // 1011 1110
#define astore	        0x3a          // 0011 1010
#define astore_0        0x4b	      // 0100 1011
#define astore_1        0x4c	      // 0100 1100
#define astore_2        0x4d	      // 0100 1101
#define astore_3        0x4e	      // 0100 1110
#define athrow	        0xbf	      // 1011 1111
#define baload	        0x33	      // 0011 0011
#define bastore	        0x54	      // 0101 0100
#define bipush	        0x10	      // 0001 0000
#define breakpoint      0xca	      // 1100 1010
#define castore	        0x55	      // 0101 0101
#define checkcast       0xc0	      // 1100 0000
#define d2f	            0x90	      // 1001 0000
#define d2i	            0x8e	      // 1000 1110
#define d2l	            0x8f	      // 1000 1111
#define dadd	        0x63	      // 0110 0011
#define daload	        0x31	      // 0011 0001
#define dastore	        0x52	      // 0101 0010
#define dcmpg	        0x98	      // 1001 1000
#define dcmpl	        0x97	      // 1001 0111
#define dconst_0	    0x0e	      // 0000 1110
#define dconst_1	    0x0f	      // 0000 1111
#define ddiv	        0x6f	      // 0110 1111
#define dload	        0x18	      // 0001 1000
#define dload_0	        0x26	      // 0010 0110
#define dload_1	        0x27	      // 0010 0111
#define dload_2	        0x28	      // 0010 1000
#define dload_3	        0x29	      // 0010 1001
#define dmul	        0x6b	      // 0110 1011
#define dneg	        0x77	      // 0111 0111
#define drem	        0x73	      // 0111 0011
#define dreturn	        0xaf	      // 1010 1111
#define dstore	        0x39	      // 0011 1001
#define dstore_0	    0x47	      // 0100 0111
#define dstore_1	    0x48	      // 0100 1000
#define dstore_2	    0x49	      // 0100 1001
#define dstore_3	    0x4a	      // 0100 1010
#define dsub	        0x67	      // 0110 0111
#define dup	            0x59	      // 0101 1001
#define dup_x1	        0x5a	      // 0101 1010
#define dup_x2	        0x5b	      // 0101 1011
#define dup2	        0x5c	      // 0101 1100
#define dup2_x1	        0x5d	      // 0101 1101
#define dup2_x2	        0x5e	      // 0101 1110
#define f2d	            0x8d	      // 1000 1101
#define f2i	            0x8b	      // 1000 1011
#define f2l	            0x8c	      // 1000 1100
#define fadd	        0x62	      // 0110 0010
#define faload	        0x30	      // 0011 0000
#define fastore	        0x51	      // 0101 0001
#define fcmpg	        0x96	      // 1001 0110
#define fcmpl	        0x95	      // 1001 0101
#define fconst_0	    0x0b	      // 0000 1011
#define fconst_1	    0x0c	      // 0000 1100
#define fconst_2	    0x0d	      // 0000 1101
#define fdiv	        0x6e	      // 0110 1110
#define fload	        0x17	      // 0001 0111
#define fload_0	        0x22	      // 0010 0010
#define fload_1	        0x23	      // 0010 0011
#define fload_2	        0x24	      // 0010 0100
#define fload_3	        0x25	      // 0010 0101
#define fmul	        0x6a	      // 0110 1010
#define fneg	        0x76	      // 0111 0110
#define frem	        0x72	      // 0111 0010
#define freturn	        0xae	      // 1010 1110
#define fstore	        0x38	      // 0011 1000
#define fstore_0	    0x43	      // 0100 0011
#define fstore_1	    0x44	      // 0100 0100
#define fstore_2	    0x45	      // 0100 0101
#define fstore_3	    0x46	      // 0100 0110
#define fsub	        0x66	      // 0110 0110
#define getfield	    0xb4	      // 1011 0100
#define getstatic	    0xb2	      // 1011 0010
#define goto	        0xa7	      // 1010 0111
#define goto_w	        0xc8	      // 1100 1000
#define i2b	            0x91	      // 1001 0001
#define i2c	            0x92	      // 1001 0010
#define i2d	            0x87	      // 1000 0111
#define i2f	            0x86	      // 1000 0110
#define i2l	            0x85	      // 1000 0101
#define i2s	            0x93	      // 1001 0011
#define iadd	        0x60	      // 0110 0000
#define iaload	        0x2e	      // 0010 1110
#define iand	        0x7e	      // 0111 1110
#define iastore	        0x4f	      // 0100 1111
#define iconst_m1	    0x02	      // 0000 0010
#define iconst_0	    0x03	      // 0000 0011
#define iconst_1	    0x04	      // 0000 0100
#define iconst_2	    0x05	      // 0000 0101
#define iconst_3	    0x06	      // 0000 0110
#define iconst_4	    0x07	      // 0000 0111
#define iconst_5	    0x08	      // 0000 1000
#define idiv	        0x6c	      // 0110 1100
#define if_acmpeq	    0xa5	      // 1010 0101
#define if_acmpne	    0xa6	      // 1010 0110
#define if_icmpeq	    0x9f	      // 1001 1111
#define if_icmpge	    0xa2	      // 1010 0010
#define if_icmpgt	    0xa3	      // 1010 0011
#define if_icmple	    0xa4	      // 1010 0100
#define if_icmplt	    0xa1	      // 1010 0001
#define if_icmpne	    0xa0	      // 1010 0000
#define ifeq	        0x99	      // 1001 1001
#define ifge	        0x9c	      // 1001 1100
#define ifgt	        0x9d	      // 1001 1101
#define ifle	        0x9e	      // 1001 1110
#define iflt	        0x9b	      // 1001 1011
#define ifne	        0x9a	      // 1001 1010
#define ifnonnull	    0xc7	      // 1100 0111
#define ifnull	        0xc6	      // 1100 0110
#define iinc	        0x84	      // 1000 0100
#define iload	        0x15	      // 0001 0101
#define iload_0	        0x1a	      // 0001 1010
#define iload_1	        0x1b	      // 0001 1011
#define iload_2	        0x1c	      // 0001 1100
#define iload_3	        0x1d	      // 0001 1101
#define impdep1	        0xfe	      // 1111 1110
#define imul	        0x68	      // 0110 1000
#define ineg	        0x74	      // 0111 0100
#define instanceof	    0xc1	      // 1100 0001
#define invokedynamic	0xba	      // 1011 1010
#define invokeinterface	0xb9	      // 1011 1001
#define invokespecial	0xb7	      // 1011 0111
#define invokestatic	0xb8	      // 1011 1000
#define invokevirtual	0xb6	      // 1011 0110
#define ior	            0x80	      // 1000 0000
#define irem	        0x70	      // 0111 0000
#define ireturn	        0xac	      // 1010 1100
#define ishl	        0x78	      // 0111 1000
#define ishr	        0x7a	      // 0111 1010
#define istore	        0x36	      // 0011 0110
#define istore_0	    0x3b	      // 0011 1011
#define istore_1	    0x3c	      // 0011 1100
#define istore_2	    0x3d	      // 0011 1101
#define istore_3	    0x3e	      // 0011 1110
#define isub	        0x64	      // 0110 0100
#define iushr	        0x7c	      // 0111 1100
#define ixor	        0x82	      // 1000 0010
#define JAVA_jsr        0xa8	      // 1010 1000
#define jsr_w	        0xc9	      // 1100 1001
#define l2d         	0x8a	      // 1000 1010
#define l2f	            0x89	      // 1000 1001
#define l2i	            0x88	      // 1000 1000
#define ladd	        0x61	      // 0110 0001
#define laload	        0x2f	      // 0010 1111
#define land	        0x7f	      // 0111 1111
#define lastore	        0x50	      // 0101 0000
#define lcmp	        0x94	      // 1001 0100
#define lconst_0	    0x09	      // 0000 1001
#define lconst_1	    0x0a	      // 0000 1010
#define ldc	            0x12	      // 0001 0010
#define ldc_w	        0x13	      // 0001 0011
#define ldc2_w	        0x14	      // 0001 0100
#define ldiv	        0x6d	      // 0110 1101
#define lload	        0x16	      // 0001 0110
#define lload_0	        0x1e	      // 0001 1110
#define lload_1	        0x1f	      // 0001 1111
#define lload_2	        0x20	      // 0010 0000
#define lload_3	        0x21	      // 0010 0001
#define lmul	        0x69	      // 0110 1001
#define lneg	        0x75	      // 0111 0101
#define lookupswitch	0xab	      // 1010 1011
#define lor	            0x81	      // 1000 0001
#define lrem	        0x71	      // 0111 0001
#define lreturn	        0xad	      // 1010 1101
#define lshl	        0x79	      // 0111 1001
#define lshr	        0x7b	      // 0111 1011
#define lstore	        0x37	      // 0011 0111
#define lstore_0	    0x3f	      // 0011 1111
#define lstore_1	    0x40	      // 0100 0000
#define lstore_2	    0x41	      // 0100 0001
#define lstore_3	    0x42	      // 0100 0010
#define lsub	        0x65	      // 0110 0101
#define lushr	        0x7d	      // 0111 1101
#define lxor	        0x83	      // 1000 0011
#define monitorenter	0xc2	      // 1100 0010
#define monitorexit	    0xc3	      // 1100 0011
#define multianewarray	0xc5	      // 1100 0101
#define JAVA_new	    0xbb	      // 1011 1011
#define newarray	    0xbc	      // 1011 1100
#define nop	            0x00	      // 0000 0000
#define pop	            0x57	      // 0101 0111
#define pop2	        0x58	      // 0101 1000
#define putfield	    0xb5	      // 1011 0101
#define putstatic	    0xb3	      // 1011 0011
#define ret	            0xa9	      // 1010 1001
#define JAVA_return	    0xb1	      // 1011 0001
#define saload	        0x35	      // 0011 0101
#define sastore	        0x56	      // 0101 0110
#define sipush	        0x11	      // 0001 0001
#define swap	        0x5f	      // 0101 1111
#define tableswitch	    0xaa	      // 1010 1010
#define wide            0xc4	      // 1100 0100
// End Instruction Set

typedef uint32_t ui32;

struct ClassFile {
    ui32 magic;
    ui32 minorVersion;
    ui32 majorVersion;
    ui32 constantPoolCount;
    struct ConstantPoolInfo (*constantPoolInfo)[1000];
    ui32 accessFlags;
    ui32 thisClass;
    ui32 superClass;
    ui32 interfacesCount;
    ui32* interfaces;
    ui32 fieldsCount;
    ui32* fields;
    ui32 methodsCount;
    ui32* methods;
    ui32 attributesCount;
    ui32* attributes;
};

int debug_bytes(char* path);
struct ClassFile* parse(char* path);
void printClassFile(struct ClassFile* class_file);
uint8_t* readfile(char* path, char* mode);
void freeClassFile(struct ClassFile* class_file);
#endif //PRACTICE_CLASSFILE_H
