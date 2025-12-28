#ifndef STRING_MAP_HPP
#define STRING_MAP_HPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
    ENTRY_EMPTY,
    ENTRY_DELETED,
    ENTRY_OCCUPIED,
} EntryState;

typedef struct
{
    char* key_;
    int value_;
    EntryState state_;
} MapEntry;

typedef struct
{
    MapEntry *entries_;
    size_t capacity_;
    size_t size_;
} Map;

unsigned long HashString(const char *str);

Map *CreateMap();

void FreeMapEntries(Map *map);

void FreeMap(Map *map);

void InsertMapEntry(Map **map, char *key, int value);

void DeleteMapEntry(Map **map, char *key);

MapEntry *FindMapEntry(const Map *map,  char *key);

Map *RehashMap(Map *map, size_t new_capacity);

void DisplayMap(Map *map);

#endif