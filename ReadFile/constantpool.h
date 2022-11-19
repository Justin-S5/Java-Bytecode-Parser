//
// Created by Justin Schaffner on 10/27/22.
//

#ifndef PRACTICE_CONSTANTPOOL_H
#define PRACTICE_CONSTANTPOOL_H
#include <stdio.h>
#include <stdlib.h>
#include "constantpool.h"

// Constant Pool Tags
#define CONSTANT_Class                  7
#define CONSTANT_Fieldref               9
#define CONSTANT_Methodref              10
#define CONSTANT_InterfaceMethodref     11
#define CONSTANT_String                 8
#define CONSTANT_Integer                3
#define CONSTANT_Float                  4
#define CONSTANT_Long                   5
#define CONSTANT_Double                 6
#define CONSTANT_NameAndType            12
#define CONSTANT_Utf8                   1
#define CONSTANT_MethodHandle           15
#define CONSTANT_MethodType             16
#define CONSTANT_InvokeDynamic          18
// End Constant Pool Tags

struct ConstantPoolInfo {
    uint32_t tag;
    union {
        struct {
            uint32_t name_index;
        } CONSTANT_Class_info;
        struct {
            uint32_t class_index;
            uint32_t name_and_type_index;
        } CONSTANT_Fieldref_info;
        struct {
            uint32_t class_index;
            uint32_t name_and_type_index;
        } CONSTANT_Methodref_info;
        struct {
            uint32_t class_index;
            uint32_t name_and_type_index;
        } CONSTANT_InterfaceMethodref_info;
        struct {
            uint32_t string_index;
        } CONSTANT_String_info;
        struct {
            uint32_t bytes;
        } CONSTANT_Integer_info;
        struct {
            uint32_t bytes;
        } CONSTANT_Float_info;
        struct {
            uint32_t high_bytes;
            uint32_t low_bytes;
        } CONSTANT_Long_info;
        struct {
            uint32_t high_bytes;
            uint32_t low_bytes;
        } CONSTANT_Double_info;
        struct {
            uint32_t name_index;
            uint32_t descriptor_index;
        } CONSTANT_NameAndType_info;
        struct {
            uint32_t length;
            uint8_t *bytes;
        } CONSTANT_Utf8_info;
        struct {
            uint32_t reference_kind;
            uint32_t reference_index;
        } CONSTANT_MethodHandle_info;
        struct {
            uint32_t descriptor_index;
        } CONSTANT_MethodType_info;
        struct {
            uint32_t bootstrap_method_attr_index;
            uint32_t name_and_type_index;
        } CONSTANT_InvokeDynamic_info;
    } info;
};
#endif //PRACTICE_CONSTANTPOOL_H
