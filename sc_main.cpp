#include <systemc.h>
#include "include/reset.hpp"

int sc_main(int argc, char** argv) {
    sc_clock clk{"clk", 10, SC_NS, 0.5, 3, SC_NS, true};
    sc_signal<bool> reset_signal;
    sc_signal<bool> active_level;

    Reset top("top");

    top.reset_signal(reset_signal);
    top.active_level(active_level);

    reset_signal = 0;
    sc_start(100, SC_NS);
    reset_signal = 1;
    sc_start(100, SC_NS);
    reset_signal = 0;
    sc_start(100, SC_NS);
    reset_signal = 1;
    sc_start(100, SC_NS);

    return 0;
}