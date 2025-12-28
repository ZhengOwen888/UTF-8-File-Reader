#include "str_helpers.h"
#include "map.h"

int main()
{
    // Map *map = CreateMap();

    // InsertMapEntry(&map, "hello", 1);
    // InsertMapEntry(&map, "world", 2);

    // MapEntry *entry1 = FindMapEntry(map, "hello");
    // MapEntry *entry2 = FindMapEntry(map, "world");

    // printf("Entry 1 Data: %d\n", entry1->value_);
    // printf("Entry 2 Data: %d\n", entry2->value_);
    // printf("Map Size: %zu\n", map->size_);
    // printf("Map Capacity: %zu\n", map->capacity_);

    // printf("Deleting Entry 1 Data\n");
    // DeleteMapEntry(&map, "hello");
    // printf("Deleting Entry 2 Data\n");
    // DeleteMapEntry(&map, "world");
    // printf("Map Size: %zu\n", map->size_);
    // printf("Map Capacity: %zu\n", map->capacity_);

    char *str = "You love the world, but the world does not love you back.";
    Map *word_freq = WordFreq(str);
    DisplayMap(word_freq);

    free(word_freq);
    return 0;
}