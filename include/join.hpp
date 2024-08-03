#ifndef JOIN_HPP_
#define JOIN_HPP_

#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include <iostream>

namespace usr {
    // join elements by  separator from first to last.
    template<typename InputIterator, typename SEPARATOR>
    std::string join(const InputIterator first, const InputIterator last, const SEPARATOR& sp) {
        const auto dist = std::distance(first, last);
        if (dist < 1) {
            return std::string("");
        } else if (dist < 2) {
            std::ostringstream ostr;
            ostr << *first;
            return ostr.str();
        } else {
            std::ostringstream ostr;
            InputIterator last1 = last;
            last1--;
            for (auto it = first; it != last1; ++it) {
                ostr << *it << sp;
            }
            ostr << *(last1);
            return ostr.str();
        }
    }

    // join elements by separator.
    template<typename Container, typename SEPARATOR>
    std::string join(const Container& c, const SEPARATOR& sp) {
        return join(c.begin(), c.end(), sp);
    }
}

#endif  // JOIN_HPP_
