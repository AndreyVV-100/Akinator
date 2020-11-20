﻿#include "Akinator.h"
#include "Libraries/Stack/Stack.h"

int main ()
{
    SetConsoleCP (1251);
    SetConsoleOutputCP (1251);
    setlocale (LC_ALL, "");

    printf ("Здравстуйте! Вас приветствует игра Акинатор!\n");

    Tree game_tree = {};
    TreeConstructor (&game_tree);
    OpenTree (&game_tree);

    int game_continue = 1;

    while (game_continue)
    {
        printf ("\n" "Выберите режим игры: \n"
                "1 - Отгадывание\n"
                "2 - Определение\n"
                "3 - Сравнение\n"
                "4 - Графическое представление результата\n"
                "5 - Сделать сохранение\n"
                "6 - Выход\n");

        int mode = -1;
        char inp[BUF_SIZE] = "";
        gets_s (inp, BUF_SIZE);
        sscanf (inp, "%d", &mode);

        switch (mode)
        {
            case (1):
                Guessing (&game_tree);
                break;
            case (2):
                Definition (&game_tree);
                break;
            case (3):
                Compare (&game_tree);
                break;
            case (4):
                CreateDump (&game_tree);
                break;
            case (5):
                SaveTree (&game_tree);
                break;
            case (6):
                printf ("Выход из игры...");
                game_continue = 0;
                break;
            default:
                printf ("Неопознанная команда!\n");
                break;
        }
    }

    TreeDestructor (&game_tree);
    return 0;
}

void TreeConstructor (Tree* tree)
{
    assert (tree);
    
    tree->head = nullptr;
    tree->size = 0;

    return;
}

void TreeDestructor (Tree* tree)
{
    assert (tree);

    if (tree->head != nullptr)
        ElementDestructor (tree->head);

    tree->head = nullptr;
    tree->size = 0;

    return;
}

element* ElementConstructor (const char* str)
{
    assert (str);

    element* el_crt = (element*) calloc (1, sizeof (*el_crt));  
    assert (el_crt);                                            
    *el_crt = {nullptr, nullptr, nullptr, nullptr};             
                                                                        
    el_crt->str = (char*) calloc (strlen (str) + 1, sizeof (char)); 
    assert (el_crt->str);                                       
    strcpy (el_crt->str, str);

    return el_crt;
}

void ElementDestructor (element* el)
{
    assert (el);

    if (el->left != nullptr)
    {
        ElementDestructor (el->left);
        el->left = nullptr;
    }

    if (el->right != nullptr)
    {
        ElementDestructor (el->right);
        el->right = nullptr;
    }

    free (el->str);
    el->str  = nullptr;
    el->prev = nullptr;
    free (el);

    return;
}

element* InsertHead (Tree* tree, const char* str)
{
    ass_ins_emp;

    cal;

    tree->head = el_crt;

    return el_crt;
}

element* InsertLeft (Tree* tree, element* el, const char* str)
{
    ass_ins_n_emp(el->left);

    cal;

    el_crt->prev = el;
    el->left     = el_crt;

    return el_crt;
}

element* InsertRight (Tree* tree, element* el, const char* str)
{
    ass_ins_n_emp (el->right);

    cal;

    el_crt->prev = el;
    el->right = el_crt;

    return el_crt;
}

void CreateDump (Tree* tree)
{
    assert (tree);
    
    FILE* graph = fopen ("Graph/out1251.dot", "w");
    assert (graph);
    fprintf (graph, "digraph G{\n" "rankdir = HR;\n node[shape=box];\n");

    size_t passed_elems = 0;

    if (tree->head)
    {
        fprintf (graph, "\"%p:\\n `%s`\";\n", tree->head, tree->head->str);
        ElementDump (graph, tree->head, &passed_elems, tree->size);
    }
    else
        fprintf (graph, "Нет элементов;\n");
    
    fprintf (graph, "}");
    fclose (graph);

    system ("win_iconv -f 1251 -t UTF8 \"Graph\\out1251.dot\" > \"Graph\\outUTF.dot\"");
    system ("dot -Tpng Graph\\outUTF.dot -o Graph\\gr.png");
    system ("start Graph\\gr.png");

    return;
}

int ElementDump (FILE* graph, element* el, size_t* passed_elems, size_t size)
{
    assert (graph);
    assert (el);
    assert (passed_elems);

    (*passed_elems)++;
    if (*passed_elems > size)
        return 1;

    if (el->left)
    {
        fprintf (graph, "\"%p:\\n `%s`\" -> \"%p:\\n `%s`\" [label = \"нет\"]\n;", 
                 el, el->str, el->left, el->left->str);

        if (ElementDump (graph, el->left, passed_elems, size))
            return 1;
    }

    if (el->left)
    {
        fprintf (graph, "\"%p:\\n `%s`\" -> \"%p:\\n `%s`\" [label = \"да\"]\n;",
            el, el->str, el->right, el->right->str);

        if (ElementDump (graph, el->right, passed_elems, size))
            return 1;
    }

    return 0;
}

// ToDo: Разбить на функции
void Guessing (Tree* gt)
{
    assert (gt);
    assert (gt->head);

    printf ("\n""Загадайте кого-нибудь (ну или что-нибудь)...\n"
            "Отвечайте на вопросы словами \"да\", \"нет\" или \"выход\"\n\n");

    element* elem_now = gt->head;

    while (1)
    {
        char ans[BUF_SIZE] = "";

        if (elem_now->left == nullptr && elem_now->right == nullptr)
        {
            printf ("Это %s?\n", elem_now->str);
            gets_s (ans, BUF_SIZE);
            
            if (strcmp (ans, "да") == 0)
            {
                printf ("Оно и верно, я ведь всё могу угадать!\n");
                return;
            }

            if (strcmp (ans, "нет") == 0)
                return AddAnswer (gt, elem_now);

            if (strcmp (ans, "выход") == 0)
                return;

            printf ("Неопознанная команда!\n");
            break;
        }

        if (elem_now->left == nullptr || elem_now->right == nullptr)
        {
            printf ("Что-то пошло не так...\n");
            return;
        }

        printf ("Это можно охарактеризовать как \"%s\"?\n", elem_now->str);
        gets_s (ans, BUF_SIZE);

        if (strcmp (ans, "да") == 0)
        {
            elem_now = elem_now->right;
            continue;
        }

        if (strcmp (ans, "нет") == 0)
        {
            elem_now = elem_now->left;
            continue;
        }

        if (strcmp (ans, "выход") == 0)
            break;

        printf ("Неопознанная команда!\n");
    }
}

void AddAnswer (Tree* gt, element* elem_now)
{
    assert (gt);
    assert (elem_now);

    char new_item[BUF_SIZE] = "";
    do
    {
        printf ("\n""А кто это был тогда? (знак `?` запрещён)\n");
        gets_s (new_item, BUF_SIZE);
    }
    while (strchr (new_item, '?'));

    InsertRight (gt, elem_now, new_item);

    do
    {
        printf ("А чем %s отличается от %s?\n"
                "Он (она, оно, они)... (знак `?` запрещён)\n",
                new_item, elem_now->str);
        gets_s (new_item, BUF_SIZE);
    }
    while (strchr (new_item, '?'));

    InsertLeft (gt, elem_now, new_item);

    char* str_swap      = elem_now->str;
    elem_now->str       = elem_now->left->str;
    elem_now->left->str = str_swap;

    printf ("Спасибо, я запомнил!\n");
    return;
}

void Definition (Tree* gt)
{
    assert (gt);
    assert (gt->head);
    
    printf ("\n""Скажите, для кого (чего) вам нужно сделать описание - и я его сделаю!\n"
            "Введите название: ");

    Stack stk = {};
    StackConstructor (&stk, TREE_DEEP);

    char who[BUF_SIZE] = "";
    gets_s (who, BUF_SIZE);

    FIND_RES result = FindElem (who, &stk, gt->head);

    switch (result)
    {
        case (FOUND):
        {
            assert (stk.size);
            printf ("%s - это ", who);

            if (stk.size == 1)
            {
                printf ("%s. Ни добавить, ни взять.\n");
                break;
            }

            element* elem_write = StackPop (&stk);
            element* elem_help = StackPop (&stk);

            while (stk.size > 0 && stk.status_error == STK_GOOD)
            {
                PropertyPrint (elem_write, elem_help, ", ");
                elem_write = elem_help;
                elem_help = StackPop (&stk);
            }

            if (stk.status_error != STK_GOOD)
            {
                printf ("Произошла ошибка стека на этапе вывода. Номер ошибки: %d."
                    " Обратитесь к разработчику.\n", stk.status_error);
                break;
            }

            PropertyPrint (elem_write, elem_help, ".\n");
            break;
        }

        case (NOT_FOUND):
            printf ("Извините, я не знаю, кто (что) это.\n");
            break;

        case (STACK_ERR):
            printf ("Произошла ошибка стека. Номер ошибки: %d."
                    " Обратитесь к разработчику.\n", stk.status_error);
            break;

        case (TREE_ERR):
            tree_error_printf;
    }

    StackDestructor (&stk);
    return;
}

void Compare (Tree* gt)
{

}

void SaveTree (Tree* gt)
{
    assert (gt);

    FILE* tree = fopen ("Graph/tree.txt", "w");
    assert (tree);

    fprintf (tree, "{DESCR}\n{version 1.0}\n{RUS}\n");
    if (SaveBranch (gt->head, tree, 0))
        printf ("Ошибка, сохранения. Плак...\n");
    else
        printf ("Сохранение прошло успешно!\n");

    fclose (tree);
    return;
}

int SaveBranch (element* el, FILE* tree, size_t num_tab)
{
    assert (el);
    assert (tree);
    
    tab;
    fprintf (tree, "[\n");
    num_tab++;

    if (el->left != nullptr && el->right != nullptr)
    {
        tab;
        fprintf (tree, "?%s?\n", el->str);
        if (SaveBranch (el->right, tree, num_tab))
            return 1;
        if (SaveBranch (el->left,  tree, num_tab))
            return 1;
    }
    else if (el->left == nullptr && el->right == nullptr)
    {
        tab;
        fprintf (tree, "`%s`\n", el->str);
    }
    else
        return 1;

    num_tab--;
    tab;
    fprintf (tree, "]\n");
    return 0;
}

void OpenTree (Tree* gt)
{
    assert (gt);
    FILE* tree = fopen ("Graph/tree.txt", "r");
    assert (tree);

    char str[BUF_SIZE] = "";
    for (size_t skip = 0; skip < 3; skip++)
        fgets (str, BUF_SIZE, tree);
    
    gt->head = OpenBranch (gt, 0, tree);
    if (gt->head == nullptr)
    {
        printf ("Внимание! Файл дерева или повреждён, или пуст!\n");
        gt->head = ElementConstructor ("Неизвестно кто");
    }

    fclose (tree);
    return;
}

element* OpenBranch (Tree* gt, size_t last_tab, FILE* tree)
{
    assert (gt);

    char str[BUF_SIZE] = "";
    get_string;
    
    // Строгая табуляция, при желании можно убрать проверку на количество табов и
    // добавить в skip_tabs другие разделители, помимо '\t'

    skip_tabs (tab1);
    if (tab1 != last_tab || strcmp (str + tab1, "["))
        return nullptr;

    get_string;
    skip_tabs (node);
    if (node != tab1 + 1)
        return nullptr;

    element* el = nullptr;

    if (str[node] == '?')
    {
        if (GetNode (str + node, '?'))
            return nullptr;
        
        el = ElementConstructor (str + node + 1);

        diving (el->right);
        diving (el->left);

        el->right->prev = el;
        el->left ->prev = el;
    }
    else if (str[node] == '`')
    {
        if (GetNode (str + node, '`'))
            return nullptr;
        el = ElementConstructor (str + node + 1);
    }
    else
        return nullptr;

    get_string;
    skip_tabs (tab2);
    if (tab1 != tab2 || strcmp (str + tab2, "]"))
    {
        Tree free_tree = {};
        TreeConstructor (&free_tree);
        free_tree.head = el;
        TreeDestructor (&free_tree);
        return nullptr;
    }
    gt->size += 1;
    return el;
}

int GetNode (char* str, const char symb)
{
    assert (str);

    if (*str != symb)
        return 1;

    char* check = strchr (str + 1, symb);

    if (check == nullptr || check[1] != '\0')
        return 1;

    *str   = '\0';
    *check = '\0';

    return 0;
}

FIND_RES FindElem (const char* str, Stack* stk, element* elem_now)
{
    assert (str);
    assert (stk);
    assert (elem_now);

    if (elem_now->left == nullptr && elem_now->right == nullptr)
    {
        if (strcmp (str, elem_now->str))
            return NOT_FOUND;
        StackPush (stk, elem_now);
        return FOUND;
    }

    if (elem_now->left == nullptr || elem_now->right == nullptr)
        return TREE_ERR;

    FIND_RES next_find = FindElem (str, stk, elem_now->left);

    if (next_find == FOUND)
    {
        StackPush (stk, elem_now);
        if (stk->status_error != STK_GOOD)
            next_find = STACK_ERR;
    }
    if (next_find != NOT_FOUND)
        return next_find;

    next_find = FindElem (str, stk, elem_now->right);

    if (next_find == FOUND)
    {
        StackPush (stk, elem_now);
        if (stk->status_error != STK_GOOD)
            next_find = STACK_ERR;
    }
    return next_find;
}

int PropertyPrint (element* elem_write, element* elem_help, const char* end)
{
    assert (elem_write);
    assert (elem_help);
    
    if (elem_write->left == nullptr || elem_write->right == nullptr)
        return 1;

    if (elem_write->left == elem_help)
        printf ("не %s%s", elem_write->str, end);
    else if (elem_write->right == elem_help)
        printf ("%s%s", elem_write->str, end);
    else
        return 1;

    return 0;
}
