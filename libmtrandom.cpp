#include <cstring>
#include <fcntl.h>
#include <random>
#include <unistd.h>
#include <cstdio>

#define likely(x) (!__builtin_expect(!(x), 0))
#define unlikely(x) __builtin_expect((x), 0)
#define unused(x) (!(x))

static bool initialized = false;
static std::mt19937 *generator = nullptr;


__attribute__((destructor))
static void destroy_generator() {
    if(generator != nullptr) {
        free(generator);
        generator = nullptr;
    }
}


static std::mt19937 &get_generator() {
    if(unlikely(generator == nullptr)) {
        std::mt19937 proto;
        generator = (std::mt19937 *)(malloc(sizeof(std::mt19937)));
        memcpy(generator, &proto, sizeof(std::mt19937));
        *generator = std::mt19937();
    }
    return *generator;
}


static void init() {
    if(likely(initialized)) {
        return;
    }

    unsigned char *sys_seed = new unsigned char[4096];

    char const path[] = "/dev/urandom";
    int fd = open(path, O_RDONLY | O_NONBLOCK);
    unused(read(fd, sys_seed, 4096));
    close(fd);

    std::seed_seq seq;
    seq.generate(sys_seed, sys_seed + 4096);
    get_generator().seed(seq);

    delete[] sys_seed;
    initialized = true;
}


extern "C" void srand(unsigned int seed) {
    get_generator().seed(seed);
    initialized = true;
}


extern "C" int rand(void) {
    init();
    return get_generator()() & 0x7FFFFFFF;
}
