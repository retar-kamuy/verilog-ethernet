#include <systemc.h>
#include <vector>
#include "include/gmii.hpp"

int sc_main(int argc, char** argv) {
    sc_clock clk{"clk", 10, SC_NS, 0.5, 3, SC_NS, true};
    sc_signal<bool> reset_signal;
    // sc_signal<bool> active_level;

    GmiiSource top("top");

    // top.reset_signal(reset_signal);
    // top.active_level(active_level);

    // reset_signal = 0;
    top._init_reset(0, 1);
    sc_start(100, SC_NS);
    // reset_signal = 1;
    top._init_reset(1, 1);
    sc_start(100, SC_NS);
    // reset_signal = 0;
    top._init_reset(0, 1);
    sc_start(100, SC_NS);
    // reset_signal = 1;
    top._init_reset(1, 1);
    sc_start(100, SC_NS);
    top._init_reset(0, 1);
    std::vector<unsigned char> data = {0, 1, 2, 3, 4};
    std::vector<int> error = {7, 8, 9};
    GmiiFrame frame(data, error);
    frame.repr();
    sc_start(100, SC_NS);

    return 0;
}
