void insert(hash_map_t *map, hash_element_t *elem) {
    double factor = compute_load_factor(map->num_keys + 1, map->map_size);
    printf("[DEBUG] factor = %.2lf\n", factor);

    if (factor >= LOAD_FACTOR) {
        printf("Beginning rehash...\n");
        map->temp = map->primary;
        map->temp_size = map->map_size;
        map->primary = calloc(map->map_size * 2, sizeof(void *));
        map->map_size *= 2;
    }

    int original = compute_index(elem->key, map->map_size);
    int index = original;
    int i = 1;

    if (map->primary[index]) {
        printf("Collision detected!\n");
        while (map->primary[index] != NULL) {
            index = (original + i * i) % map->map_size;
            i++;
        }
    }

    printf("Inserting %s at %d\n", elem->key, index);
    map->primary[index] = elem;
    map->num_keys++;

    rehash_inc(map);
}
