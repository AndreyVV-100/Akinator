#include "Akinator.h"

int main ()
{
    SetConsoleCP (1251);
    SetConsoleOutputCP (1251);
    setlocale (LC_ALL, "");

    printf ("Здравстуйте! Вас приветствует игра Акинатор!\n");

    Tree game_tree = {};
    TreeConstructor (&game_tree);

    InsertHead (&game_tree, "Неизвестно кто");

    int game_continue = 1;

    while (game_continue)
    {
        printf ("\n" "Выберите режим игры: \n"
                "1 - Отгадывание\n"
                "2 - Определение\n"
                "3 - Сравнение\n"
                "4 - Графическое представление результата\n"
                "5 - Выход\n");

        int mode = -1;
        char inp[256] = "";
        gets_s (inp, 256);
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

void Guessing (Tree* gt)
{
    assert (gt);
    assert (gt->head);

    printf ("\n""Загадайте кого-нибудь (ну или что-нибудь)...\n"
            "Отвечайте на вопросы словами \"да\", \"нет\" или \"выход\"\n\n");

    element* elem_now = gt->head;

    while (1)
    {
        char ans[256] = "";

        if (elem_now->left == nullptr && elem_now->right == nullptr)
        {
            printf ("Это %s?\n", elem_now->str);
            gets_s (ans, 256);
            
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
        gets_s (ans, 256);

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

    printf ("\n""А кто это был тогда?\n");
    char new_item[256] = "";
    gets_s (new_item, 256);
    InsertRight (gt, elem_now, new_item);

    printf ("А чем это отличается от %s?\n"
            "Он (она, оно, они)...\n", elem_now->str);
    gets_s (new_item, 256);
    element* new_elem = ElementConstructor (new_item);
    InsertLeft (gt, elem_now, new_item);

    char* str_swap      = elem_now->str;
    elem_now->str       = elem_now->left->str;
    elem_now->left->str = str_swap;

    printf ("Спасибо, я запомнил!\n");
    return;
}

void Definition (Tree* gt)
{

}

void Compare (Tree* gt)
{

}

void SaveTree (Tree* gt)
{
    assert (gt);

    FILE* tree = fopen ("Graph/tree.txt", "w");

}
