#ifndef _CPPREF_WEIGHTEDJOB_H_
#define _CPPREF_WEIGHTEDJOB_H_

#include <string>

using std::string;

/**
 * Basic example of an order-able type.
 */
class WeightedJob {
public:
    double weight;
    double length;
    WeightedJob();
    WeightedJob(double weight, double length);
    WeightedJob(string weight, string length);
    static bool higherPriorityRatio(const WeightedJob& self, const WeightedJob& other);
    bool operator > (const WeightedJob& other) const;
    bool operator == (const WeightedJob& other) const;
    bool operator < (const WeightedJob& other) const;
    double getPriority() const;
};

#endif //_CPPREF_WEIGHTEDJOB_H_
