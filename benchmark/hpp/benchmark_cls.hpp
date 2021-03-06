#ifndef BENCHMARK_CLS_HPP
#define BENCHMARK_CLS_HPP

#include "../lib/cpp11nullptr/lsignal/lsignal.h"

#include "../../benchmark.hpp"

class Cls
{
    SlotScope reg;

    NOINLINE(void handler(Rng& rng))
    {
        volatile std::size_t a = rng(); (void)a;
    }

    public:
    
    // Had to add namespace, always namespace
    using SignalType = lsignal::signal<void(Rng&)>;

    template <typename Subject, typename Foo>
    static void connect_method(Subject& subject, Foo& foo)
    {
		auto reg = subject.connect(&foo, &Foo::handler);
        // Automatically disconnect when the foo instance is destroyed
        // Benchmarks require connection management
        foo.reg = make_slot_scope([reg, &subject](void*) { subject.disconnect(reg); });
    }
    template <typename Subject>
    static void emit_method(Subject& subject, Rng& rng)
    {
        subject(rng);
    }

    static void validate_assert(std::size_t);
    static double construction(std::size_t);
    static double destruction(std::size_t);
    static double connection(std::size_t);
    static double emission(std::size_t);
    static double combined(std::size_t);

    // This may or may not be implemented
    static double threaded(std::size_t);

    static const char* LibraryName;
};

#endif // BENCHMARK_CLS_HPP