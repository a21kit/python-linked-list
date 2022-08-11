#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
    int data;
    struct Node* next;
};

// create a node with data as x
struct Node* create_node(int x) {
    struct Node* ptr = malloc(sizeof(struct Node));
    ptr->next = NULL;
    ptr->data = x;
    return ptr;
}

// delete the node at `ptr` and free its memory
void delete_node(struct Node* ptr) {
    free(ptr);
}

// ------------------------------ Node struct definition ends here ------------------------------

// Use this to operate on the list, this will always point at the head of the list.
struct Node* PythonListHead = NULL;


// prints the list in space seperated format
void print_list(struct Node* head) {
    struct Node* cur = head;
    while(cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}


// Add an item to the end of the list
void append(int x) {
    struct Node* last = PythonListHead;
    if (PythonListHead == NULL){
        PythonListHead = create_node(x);
        return;
    }
    while (last->next != NULL){
        last = last->next;
    }
    struct Node* new_data;
    new_data = create_node(x);
    last->next = new_data;
    return;
}


// Insert an item at a given position. 
// The first argument is the index of the element before which to insert
// second argument is the value to insert at that position
// if the position does not exist, do nothing
void insert(int position, int x) {
    struct Node* ele = PythonListHead;
    if (position < 0){
        return;
    }
    int i = 0;
    if (position == 0){
        struct Node* new = create_node(x);
        new->next = PythonListHead;
        PythonListHead = new;
    }
    while (i != position-1){
        if (ele == NULL){
            return;
        }
        ele = ele->next;
        i++;
    }
    struct Node* new = create_node(x);
    new->next = ele->next;
    ele->next = new; 
    return;  
}


// Remove the item at the end of the list
void pop() {
    struct Node* curr = PythonListHead;
    if (curr != NULL){
        if (curr->next != NULL){
            while(curr->next->next != NULL){
                curr = curr->next;
            }
            delete_node(curr->next);
            curr->next = NULL;
            return;
        }
        else{
            delete_node(PythonListHead);
            PythonListHead = NULL;
            return;
        }
    }
}


// Remove all items from the list
void clear() {
    struct Node* temp = PythonListHead;
    struct Node* bin = NULL;
    while (temp->next != NULL){
        bin = temp;
        temp = temp->next;
        delete_node(bin);
    }
    delete_node(temp);
    PythonListHead = NULL;
    return;
}


// Return the number of times x appears in the list.
int count(int x) {
    int s = 0;
    struct Node* ele = PythonListHead;
    while (ele != NULL){
        if (ele->data == x){
            s++;
        }
        ele = ele->next;
    }
    return s;
}


// Reverse the elements of the list in place.
// Make sure you change `PythonListHead` accordingly
void reverse() {
    struct Node* next = NULL;
    struct Node* curr = PythonListHead;
    struct Node* prev = NULL;
    while (curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    PythonListHead = prev;
    return;
}


// Return the number of elements in the list
int len() {
    int l = 0;
    struct Node* ele = PythonListHead;
    while (ele != NULL){
        l++;
        ele = ele->next;
    }
    return l;
}


// Set the data attribute of the node at `position` to `x`
// if no such position, do nothing
void setitem(int position, int x) {
    if (position<0){
        return;
    }
    struct Node* curr = PythonListHead;
    for (int i=0; i<position; i++){
        if (curr == NULL){
            return;
        }
        curr = curr->next;
    }
    curr->data = x;
}


// Return the data of the node at `position` 
// if no such position, return -1
int getitem(int position) {
    struct Node* curr = PythonListHead;
    if (position < 0){
        return -1;
    }
    for (int i=0; i<position; i++){
        if (curr == NULL){
            return -1;
        }
        curr = curr->next;
    }
    return curr->data;
}


// erase the node at position
// if no such position, do nothing
void erase(int position) {
    struct Node* curr = PythonListHead;
    if (position < 0){
        return;
    }
    if (position == 0){
        PythonListHead = PythonListHead->next;
        return;
    }
    for (int i=0; i<position-1; i++){
        if (curr == NULL){
            return;
        }
        curr = curr->next;
    }
    struct Node* temp = curr->next;
    curr->next = curr->next->next;
    delete_node(temp);
    temp=NULL;
    return;
}


// Returns a the head of the newly formed Python List
// containing elements present in positions in the original List.
// Note: you have to create new Python List and return its head.
// Here positions is an array of size n.
// eg. if positions = [2, 3, 5], you need to return a newly formed list
// having nodes that were at position 2, 3 and 5 in the original list.
// if there is such a position that is not present in the original list, do nothing
// with that position.
struct Node* index_into(int *positions, int n) {
    struct Node* new_list = NULL;
    int arr[n];
    for (int i=0; i<n; i++){
        arr[i] = getitem(positions[i]);
    }
    int k = 0;
    for (int j=0; j<n; j++){
        if (arr[j] != -1){
            if (new_list == NULL){
                new_list = create_node(arr[j]);
                continue;
            }
            struct Node* curr = new_list;
            while (curr->next != NULL){
                curr = curr->next;
            }
            struct Node* new_data = create_node(arr[j]);
            curr->next = new_data;
            curr = curr->next;
        }
    }
    return new_list;
}


// swaps the nodes present at `position` and `position+1`
// if either of  `position` or `position+1` does not exist, do nothing
void swap(int position) {
    if (getitem(position) == -1 || getitem(position+1) == -1){
        return;
    }
    struct Node* curr = PythonListHead;
    struct Node* temp = NULL;
    if (position == 0){
        temp = PythonListHead;
        curr = PythonListHead->next;
        PythonListHead = curr;
        temp->next = PythonListHead->next;
        PythonListHead->next = temp;
    }
    else{
        for (int i=0; i<position-1; i++){
            curr = curr->next;
        }
        temp = curr->next;
        curr->next = temp->next;
        temp->next = curr->next->next;
        curr->next->next = temp;
    }
}


// sort the Python list
// you may use the above defined swap function to 
// implement bubble sort. But its upto you, use whatever algorithm
// that you seem comfortable.
void sort() {
        int n = len();
    for (int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            int y = getitem(i);
            int x = getitem(j);            
            if (x<y){
                setitem(i,x);
                setitem(j,y);
            }
        }
    }
}


// ----------------------- Driver program starts here -----------------------

int main(int argc, char const *argv[])
{
    int T; 
    scanf("%d", &T);

    char operation_type[20];
    int indices[100];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "append") == 0) {
            int x;
            scanf("%d", &x);
            append(x);
        } 

        if(strcmp(operation_type, "insert") == 0) {
            int pos, x;
            scanf("%d %d", &pos, &x);
            insert(pos, x);
        }

        if(strcmp(operation_type, "pop") == 0) {
            pop();
        }

        if(strcmp(operation_type, "clear") == 0) {
            clear();
        }

        if(strcmp(operation_type, "count") == 0) {
            int x;
            scanf("%d", &x);
            int cnt = count(x);
            printf("%d\n", cnt);
        }

        if(strcmp(operation_type, "reverse") == 0) {
            reverse();
        }

        if(strcmp(operation_type, "len") == 0) {
            int length = len();
            printf("%d\n", length);
        }

        if(strcmp(operation_type, "setitem") == 0) {
            int pos, x;
            scanf("%d %d", &pos, &x);
            setitem(pos, x);
        }

        if(strcmp(operation_type, "getitem") == 0) {
            int pos;
            scanf("%d", &pos);
            int value = getitem(pos);
            printf("%d\n", value);
        }

        if(strcmp(operation_type, "print") == 0) {
            print_list(PythonListHead);
        }

        if(strcmp(operation_type, "erase") == 0) {
            int pos;
            scanf("%d", &pos);
            erase(pos);
        }

        if(strcmp(operation_type, "swap") == 0) {
            int pos;
            scanf("%d", &pos);
            swap(pos);
        }

        if(strcmp(operation_type, "index_into") == 0) {
            int n;
            scanf("%d", &n);
            for(int i=0;i<n;i++) scanf("%d", &indices[i]);
            struct Node* new_head = index_into(indices, n);
            print_list(new_head);
        }

        if(strcmp(operation_type, "sort") == 0) {
            sort();
        }
    }
}