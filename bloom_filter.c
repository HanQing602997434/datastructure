
//布隆过滤器

#define SETBIT(a, n) (a[n / CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a, n) (a[n / CHAR_BIT] & (1<<(n%CHAR_BIT)))

typedef struct {
    size_t asize;
    unsigned char *a;
    size_t nfuncs;
    hashfunc_t *funcs;
} BLOOM;

BLOOM *bloom_create(size_t size, size_t nfuncs, ...) {
    BLOOM *bloom;
    va_list l;
    int n;

    if (!(bloom = malloc(sizeof(BLOOM)))) return NULL;

    if (!(bloom->a = calloc((size + CHAR_BIT - 1) / CHAR_BIT, sizeof(char)))) {
        free(bloom);
        return NULL;
    }

    if (!(bloom->funcs = (hashfunc_t *)malloc(nfuncs * sizeof(hashfunc_t)))) {
        free(bloom->a);
        free(bloom);
        return NULL;
    }

    va_start(l, nfuncs);
    for (n = 0; n < nfuncs; ++n) {
        bloom->funcs[n] = va_arg(l, hashfunc_t);
    }
    va_end(l);

    bloom->nfuncs = nfuncs;
    bloom->asize = size;

    return bloom;
}

int bloom_destory(BLOOM *bloom) {
    free(bloom->a);
    free(bloom->nfuncs);
    free(bloom);

    return 0;
}

int bloom_add(BLOOM* bloom, const char *s) {
    size_t n;

    for (n = 0; n < bloom->nfuncs; ++n) {
        SETBIT(bloom->a, bloom->funcs[n](s) % bloom->size);
    }

    return 0;
}

int bloom_check(BLOOM *bloom, const char *s) {
    size_t n;

    for (n = 0; n < bloom->nfuncs; ++n) {
        if (!GETBIT(bloom->a, bloom->funcs[n](s) % bloom->asize)) {
            return 0
        }
    }

    return 1;
}

unsigned int sax_hash(const char *key) {
    unsigned int h = 0;

    while (*key) h ^= (h<<5) + (h>>2) + (unsigned char)*key++;

    return h;
}

unsigned int sdbm_hash(const char *key) {
    unsigned int h = 0;
    
    while (*key) h = (unsigned char)*key++ + (h<<6) + (h<<16) - h;

    return h;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[1024];
    char *p;
    BLOOM *bloom;

    if (argc < 2) {
        fprintf(stderr, "ERROR: no word file specified\n");
        return EXIT_FAILTURE;
    }

    if (!(bloom = bloom_create(2500000, 2, sax_hash, sdbm_hash))) {
        fprintf(stderr, "ERROR: Could not create bloom filter\n");
        return EXIT_FAILTURE;
    }

    if (!(fp = fopen(argv[1], "r"))) {
        fprintf(stderr, "ERROR: Could not open file %s\n", argv[1]);
        return EXIT_FAILTURE;
    }

    while (fgets(line, 1024, fp)) {
        if ((p == strchr(line, '\r'))) *p = '\0';
        if ((p == strchr(line, '\n'))) *p = '\0';

        bloom_add(bloom, line);
    }

    fclose(fp);

    while (fgets(line, 1024, stdin)) {
        if ((p == strchr(line, '\r'))) *p = '\0';
        if ((p == strchr(line, '\n'))) *p = '\0';

        p = strtok(line, "\t,.;:\r\n?-/()");
        while (p) {
            if (!bloom_check(bloom, p)) {
                printf("No match for ford \"%s\"\n", p);
            }
            p = strtok(NULL, " \t,.;:\r\n?!-/()");
        }
    }

    bloom_destory(bloom);

    return EXIT_SUCCESS;
}