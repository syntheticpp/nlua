#ifndef NLUA_TEST_VALUE_H
#define NLUA_TEST_VALUE_H


class Double
{
public:


    Double() : v(0)
    {}

    // TODO
    Double(double in) : v(in) {}

    ~Double() 
    {
    }

    void set(double d)
    { 
        //cout << "called: Double::set(" << d << ")\n";
        v    = d;
    }

    double get()
    { 
        //cout << "called: Double::get(): " << v << " returned, this="<<this<<" \n";
        return v;
    }

private:
    double v;
};


#endif
