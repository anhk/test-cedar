

#include "cedar.h"

struct str_dict {
    const char *key;
    int value;
};

struct str_dict dict[] = {
    {"http://www.baidu.com/", 9999},
    {"http://www.baidu.com/a", 9989},
    {"http://www.sohu.com/", 9998},
    {"http://www.sina.com/", 9997},
};


struct str_dict match[] = {
    {"http://", 0},
    {"baidu", 0},
    {"http://www.baidu.com/", 0},
    {"http://www.baidu.com", 0},
    {"http://www.baidu.com/aaaa", 0},
};

int main(int argc, char **argv)
{
    int count = sizeof(dict) / sizeof(dict[0]);
    printf("dict items: %d\n", count);

    const size_t NUM_RESULT = 1024;

    cedar::da <int> trie;
    cedar::da<int>::result_pair_type result_pair[NUM_RESULT];

    for (int i = 0; i < count; i ++) {
        printf("> %s %d\n", dict[i].key, dict[i].value);
        trie.update(dict[i].key, strlen(dict[i].key), dict[i].value);
    }

    count = sizeof(match) / sizeof(match[0]);

    for (int i = 0; i < count; i ++) {
        size_t ret = trie.commonPrefixSearch (match[i].key, result_pair, NUM_RESULT);
        printf("<%s> match: %ld\n", match[i].key, ret);

        for (int j = 0; j < ret; j ++) {
            printf(" return: %d\n", result_pair[j].value);
        }
    }

    return 0;
}

