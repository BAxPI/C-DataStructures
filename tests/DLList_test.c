#include "../DLList.h"
#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef assert
#undef assert
#endif
#define assert(x) (result = result && (x))

//Static variables 
static int result;
static int expected_code;
static int should_exit;
static jmp_buf jump_env;
static int done;
static int num_tests;
static int tests_passed;

void test_start(char *name){
    num_tests++;
    result = 1;
    printf("-- Testing %s ...", name);
}

void test_end(){
    if (result) tests_passed++;
    printf("%s\n", result ? "success" : "fail");
}

void exit(int code){
    if (!done){
        assert(should_exit==1);
        assert(expected_code==code);
        longjmp(jump_env, 1);
    }
    else{
        _exit(code);
    }
}

/** Vector3d for testing **/
struct Vector3d{ 
    /* data */
    int x; int y; int z;
};

void * ctor(void * item){
    struct Vector3d *vector = (struct Vector3d *)malloc(sizeof(struct Vector3d)); 
    memcpy(vector, item, sizeof(struct Vector3d));
    return vector;
}

void dtor(void * item){
    free(item);
}

int compare(void * item1, void * item2){
    struct Vector3d *elem1 = (struct Vector3d *)item1;
    struct Vector3d *elem2 = (struct Vector3d *)item2;
    float size1 = sqrt(elem1->x*elem1->x + elem1->y*elem1->y + elem1->z*elem1->z);
    float size2 = sqrt(elem2->x*elem2->x + elem2->y*elem2->y + elem2->z*elem2->z);

    return (size1 > size2) - (size1 < size2); 
}

void print_vector3d(void * item){
    printf("(%d, %d, %d)", ((struct Vector3d *)item)->x ,((struct Vector3d *)item)->y, ((struct Vector3d *)item)->z);
}


/*** Testing Cases ***/
// Testing creation of DLList
void DLList_new_t(){
    int f;
    struct DLList *my_list = DLList_new(ctor, dtor, compare, print_vector3d);
    test_start("Creation of DDList");
    should_exit = 1;
    if(my_list) f  = 1;
    assert(f == 1);    
    DLList_destroy(my_list);
    test_end();
}

void destroy_empty_list(){
    test_start("Destroy an empty list");
    should_exit = 1;
    assert(DLList_destroy(NULL) == true);
    test_end();
}

void DLList_add_elements(){
    struct DLList *my_list = DLList_new(ctor, dtor, compare, print_vector3d);
    struct Vector3d vector1, vector2;
    vector1.x = 5, vector1.y = 5, vector1.z = 5;
    vector2.x = 10, vector2.y = 10, vector2.z = 5;

    test_start("Add first node");
    should_exit = 1;
    assert(DLList_add(my_list, &vector1) == true);
    assert(DLList_add(my_list, &vector2) == true);
    DLList_destroy(my_list);
    test_end();
}

void DLList_delete_head(){
    struct DLList *my_list = DLList_new(ctor, dtor, compare, print_vector3d);
    struct Vector3d vector1 = {0}, vector2 = {0}, vector3 = {0};
    vector1.x = 5, vector1.y = 5, vector1.z = 5;
    vector2.x = 10, vector2.y = 10, vector2.z = 5;
    vector3.x = 10, vector3.y = 20, vector3.z = 5;

    test_start("Head deletion");
    should_exit = 0;
    DLList_add(my_list, &vector1);
    DLList_add(my_list, &vector2);
    DLList_add(my_list, &vector3);
    assert(DLList_delete(my_list, &vector3) == true);
    DLList_destroy(my_list);
    test_end();
}

void DLList_delete_tail(){
    struct DLList *my_list = DLList_new(ctor, dtor, compare, print_vector3d);
    struct Vector3d vector1, vector2, vector3;
    vector1.x = 5, vector1.y = 5, vector1.z = 5;
    vector2.x = 10, vector2.y = 10, vector2.z = 5;
    vector3.x = 10, vector2.y = 20, vector2.z = 5;

    test_start("Tail deletion");
    should_exit = 0;
    DLList_add(my_list, &vector1);
    DLList_add(my_list, &vector2);
    DLList_add(my_list, &vector3);
    assert(DLList_delete(my_list, &vector1) == true);
    DLList_destroy(my_list);
    test_end();

}
void DLList_delete_middle(){
    struct DLList *my_list = DLList_new(ctor, dtor, compare, print_vector3d);
    struct Vector3d vector1, vector2, vector3;
    vector1.x = 5, vector1.y = 5, vector1.z = 5;
    vector2.x = 10, vector2.y = 10, vector2.z = 5;
    vector3.x = 10, vector2.y = 20, vector2.z = 5;

    test_start("Node in the middle deletion");
    should_exit = 1;
    DLList_add(my_list, &vector1);
    DLList_add(my_list, &vector2);
    DLList_add(my_list, &vector3);
    assert(DLList_delete(my_list, &vector2) == true);
    DLList_destroy(my_list);
    test_end();
}

int main(void){
    num_tests = 0;
    tests_passed = 0;
    done = 0;

    // Running the tests
    printf("=============================================");
    printf("\n--- DLList Tests --- \n");
    DLList_new_t();
    destroy_empty_list();
    DLList_add_elements();
    DLList_delete_head();
    DLList_delete_tail();
    DLList_delete_middle();

    printf("Total tests passed: %d\n", tests_passed);
    printf("============================================\n");
    done = 1;
    return !(tests_passed == num_tests);

    return 0;
}
