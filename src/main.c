#include "str_helpers.h"
#include "map.h"

int main()
{
    // char *str = "You love the world, but the world does not love you back.";

    // printf("String: %s\n", str);
    // printf("Word Count: %d\n", WordCount(str));
    // printf("Character Count: %d\n", CharacterCount(str));
    Map *map = CreateMap();

    InsertMapEntry(&map, "hello", 1);
    InsertMapEntry(&map, "world", 2);

    MapEntry *entry1 = GetMapEntry(map, "hello");
    MapEntry *entry2 = GetMapEntry(map, "world");

    printf("Entry 1 Data: %d\n", entry1->value_);
    printf("Entry 2 Data: %d\n", entry2->value_);
    printf("Map Size: %zu\n", map->size_);
    printf("Map Capacity: %zu\n", map->capacity_);

    printf("Deleting Entry 1 Data\n");
    DeleteMapEntry(&map, "hello");
    printf("Deleting Entry 2 Data\n");
    DeleteMapEntry(&map, "world");
    printf("Map Size: %zu\n", map->size_);
    printf("Map Capacity: %zu\n", map->capacity_);


    return 0;
}