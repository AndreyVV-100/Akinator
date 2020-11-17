#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#pragma warning (disable : 4996)

#define ass_ins_emp assert (tree);                  \
                    assert (str);                   \
                    assert (tree->head == nullptr); \
                    assert (tree->size == 0);

#define ass_ins_n_emp(pos)  assert (tree);                  \
                            assert (str);                   \
                            assert (el);                    \
                            assert (tree->head != nullptr); \
                            assert (tree->size != 0);       \
                            assert (pos == nullptr);

#define cal element* el_crt = ElementConstructor (str); \
            tree->size += 1;

struct element
{
    element* prev  = nullptr;
    element* left  = nullptr;
    element* right = nullptr;
    char* str      = nullptr;
};

struct Tree
{
    element* head = nullptr;
    size_t size = 0;
};

void TreeConstructor (Tree* tree);

void TreeDestructor (Tree* tree);

element* ElementConstructor (const char* str);

void ElementDestructor (element* el);

element* InsertHead (Tree* tree, const char* str);

element* InsertLeft  (Tree* tree, element* el, const char* str);

element* InsertRight (Tree* tree, element* el, const char* str);

void CreateDump (Tree* tree);

int ElementDump (FILE* graph, element* el, size_t* passed_elems, size_t size);

void Guessing (Tree* gt);

void Definition (Tree* gt);

void Compare (Tree* gt);

void AddAnswer (Tree* gt, element* elem_now);

void SaveTree (Tree* gt);
