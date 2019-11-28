#ifndef HASHMAP_H
#define HASHMAP_H
typedef node node
typedef hashmap hashmap
struct node {
    int key;
    int value;
    node *list_of_nodes;
};

/**
a hash map object specified with it's size and a table of elements
*/
struct hashmap{
    int size;
    node *list_of_nodes;
};

hashma *createhashMap(int size){
    hashmap *t = (hashmap*)malloc(sizeof(table));
    t->size = size;
    t->list = (node**)malloc(sizeof(node*)*size);
    int i;
    for(i=0;i<size;i++)
        t->list[i] = NULL;
    return t;
}

class hashmap
{
    public:
        hashmap();
        virtual ~hashmap();

    protected:

    private:

};

#endif // HASHMAP_H
