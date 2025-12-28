#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

unsigned long HashString(const char* str)
{
    unsigned long hash = 5983;
    int ch = 0;

    while ((ch = *str++))
    {
        hash = ((hash << 5) + hash) + ch;
    }

    return hash;
}

Map *CreateMap()
{
    Map *map = calloc(1, sizeof(Map));
    if (map == NULL)
    {
        perror("Calloc failed to allocate for Map.");
        exit(1);
    }

    map->entries_ = calloc(2, sizeof(MapEntry));
    if (map->entries_ == NULL)
    {
        perror("Calloc failed to allocate for MapEntry.");
        exit(1);
    }

    map->capacity_ = 2;
    map->size_ = 0;

    return map;
}

void FreeMapEntries(Map *map)
{
    for (int i = 0; i < map->capacity_; i++)
    {
        free(map->entries_[i].key_);
    }
}

void FreeMap(Map *map)
{
    FreeMapEntries(map);
    free(map->entries_);
    free(map);
}

void InsertMapEntry(Map **map, char *key, int value)
{
    unsigned long hash = HashString(key);
    unsigned long start_bucket = hash % (*map)->capacity_;
    unsigned long bucket = start_bucket;
    MapEntry *entries = (*map)->entries_;
    MapEntry *deleted_entry = NULL;

    while (entries[bucket].state_ != ENTRY_EMPTY)
    {
        if (entries[bucket].state_ == ENTRY_OCCUPIED
        &&  strcmp(entries[bucket].key_, key) == 0)
        {
            return;
        }

        if (entries[bucket].state_ == ENTRY_DELETED && deleted_entry == NULL)
        {
            deleted_entry = &entries[bucket];
        }

        bucket = (bucket + 1) % (*map)->capacity_;

        if (bucket == start_bucket)
        {
            return;
        }
    }

    if (deleted_entry != NULL)
    {
        free(deleted_entry->key_);
        deleted_entry->key_ = strdup(key);
        deleted_entry->value_ = value;
        deleted_entry->state_ = ENTRY_OCCUPIED;
    }
    else
    {
        entries[bucket].key_ = strdup(key);
        entries[bucket].value_ = value;
        entries[bucket].state_ = ENTRY_OCCUPIED;
    }

    (*map)->size_++;

    if ((double)(*map)->size_ / (*map)->capacity_ >= 0.7)
    {
        (*map) = RehashMap((*map), (*map)->capacity_ * 2);
    }
}

void DeleteMapEntry(Map **map, char *key)
{
    MapEntry *entry = FindMapEntry(*map, key);
    if (entry != NULL)
    {
        free(entry->key_);
        entry->value_ = 0;
        entry->state_ = ENTRY_DELETED;
    }

    (*map)->size_--;

    if ((*map)->capacity_ > 2 && (double)(*map)->size_ / (*map)->capacity_ < 0.5f)
    {
        (*map) = RehashMap((*map), (*map)->capacity_ / 2);
    }
}

MapEntry *FindMapEntry(const Map *map, char *key)
{
    unsigned long hash = HashString(key);
    unsigned long start_bucket = hash % map->capacity_;
    unsigned long bucket = start_bucket;
    MapEntry *entries = map->entries_;

    while (entries[bucket].state_ != ENTRY_EMPTY)
    {
        if (entries[bucket].state_ == ENTRY_OCCUPIED
        &&  strcmp(entries[bucket].key_, key) == 0)
        {
            return &(entries[bucket]);
        }

        bucket = (bucket + 1) % map->capacity_;

        // detect cycle
        if (bucket == start_bucket)
        {
            return NULL;
        }
    }
    return NULL;
}

Map *RehashMap(Map *map, size_t new_capacity)
{
    Map *new_map = calloc(1, sizeof(Map));
    if (new_map == NULL)
    {
        perror("Calloc failed to allocate for Map.");
        exit(1);
    }

    new_map->entries_ = calloc(new_capacity, sizeof(MapEntry));
    if (new_map->entries_ == NULL)
    {
        perror("Calloc failed to allocate for MapEntry.");
    }

    new_map->capacity_ = new_capacity;
    for (int bucket = 0; bucket < map->capacity_; bucket++)
    {
        MapEntry *entry = &(map->entries_[bucket]);
        if (entry->state_ == ENTRY_OCCUPIED)
        {
            InsertMapEntry(&new_map, entry->key_, entry->value_);
        }
    }

    FreeMap(map);
    return new_map;
}

void DisplayMap(Map *map)
{
    for (size_t bucket = 0; bucket < map->capacity_; bucket++)
    {
        MapEntry *entry = &(map->entries_[bucket]);

        if (entry->state_ == ENTRY_OCCUPIED)
        {
            printf("Key: %10s | Value: %d\n", entry->key_, entry->value_);
        }
    }
}