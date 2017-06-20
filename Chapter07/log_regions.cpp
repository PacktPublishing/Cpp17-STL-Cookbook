#include <iostream>
#include <fstream>

using namespace std;

class redirect_cout_region {
    using buftype = decltype(cout.rdbuf());

    ofstream ofs;
    buftype buf_backup;

public:
    explicit redirect_cout_region(const string &filename)
        : ofs{filename}, buf_backup{cout.rdbuf(ofs.rdbuf())}
    {}

    redirect_cout_region()
        : ofs{}, buf_backup{cout.rdbuf(ofs.rdbuf())}
    {}

    ~redirect_cout_region() { cout.rdbuf(buf_backup); }
};

void my_output_heavy_function()
{
    cout << "some output\n";
    cout << "this function does really heavy work\n";
    cout << "... and lots of it...\n";
    // ...
}

int main()
{
    cout << "Readable from normal stdout\n";

    {
        redirect_cout_region _ {"output.txt"};
        cout << "Only visible in output.txt\n";
        my_output_heavy_function();
        redirect_cout_region _2 {"fofo.txt"};
        cout << "fofo\n";
    }

    {
        redirect_cout_region _;
        cout << "This output will completely vanish\n";
    }

    cout << "Readable from normal stdout again\n";
}
