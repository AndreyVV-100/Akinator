#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <locale.h>
#define TX_USE_SPEAK
#include "Libraries/TX/TXLib.h"
#include <windows.h>

#pragma warning (disable : 4996)

#define Speak(...) FuncSpeak (__VA_ARGS__, nullptr)

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

#define tab for (size_t i_tab = 0; i_tab < num_tab; i_tab++)   \
                fprintf (tree, "\t");

#define skip_tabs(tabs) size_t tabs = 0;            \
                        while (str[tabs] == '\t')   \
                            tabs++;

#define diving(where_to)    where_to = OpenBranch (gt, last_tab + 1, tree); \
                            if (where_to == nullptr)                        \
                            {                                               \
                                ElementDestructor (el);                     \
                                return nullptr;                             \
                            }

#define get_string  if (fgets (str, BUF_SIZE, tree) == nullptr) \
                        return nullptr;                         \
                    {                                           \
                        char* no_slash_n = strchr (str, '\n');  \
                        if (no_slash_n)                         \
                            *no_slash_n = '\0';                 \
                    }

#define tree_error_printf {                                                                      \
                          printf ("\n""Ошибка: дерево повреждено. Обратитесь к разработчику.\n");\
                          break;                                                                 \
                          }

const size_t BUF_SIZE  = 256;
const size_t TREE_DEEP = 256;

enum FIND_RES
{
    NOT_FOUND  = 0,
    FOUND      = 1,
    STACK_ERR  = 2,
    TREE_ERR   = 3
};

struct Stack;

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

void FuncSpeak (const char* first_str, ...);

void SpeakFormat (const char* format, ...);

void Guessing (Tree* gt);

void Definition (Tree* gt);

void Compare (Tree* gt);

void SaveTree (Tree* gt);

int SaveBranch (element* el, FILE* tree, size_t num_tab);

void OpenTree (Tree* gt);

element* OpenBranch (Tree* gt, size_t last_tab, FILE* tree);

int GetNode (char* str, const char symb);

int AskObject (element* elem_now, char* ans, Tree* gt);

void AddAnswer (Tree* gt, element* elem_now);

element* AskProperty (element* elem_now, char* ans);

FIND_RES FindElem (const char* str, Stack* stk, element* elem_now);

int AllPropertiesPrint (Stack* stk, const char* who);

int PropertyPrint (element* elem_write, element* elem_help, const char* end);

void Modes23PrintError (FIND_RES result);

void CompareElements (Stack* stk1, Stack* stk2, const char* who1, const char* who2);

char* Stpcpy (char* copy_place, const char* copy_str);
