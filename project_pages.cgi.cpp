#include <iostream>
#include "fcgio.h"

using namespace std;

int main(void) {
    // Backup the stdio streambufs
    streambuf * cin_streambuf  = cin.rdbuf();
    streambuf * cout_streambuf = cout.rdbuf();
    streambuf * cerr_streambuf = cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);

        cout << "Content-type: text/html\r\n"
             << "\r\n"
             << "<html>\n"
             << "  <head>\n"
             << "    <title>Karl Diedrich, PhD projects</title>\n"
             << "  </head>\n"
             << "  <body>\n"
             << "    <h1>Project pages</h1>\n"
             << "   <h2>Fast CGI</h2>\n"
             << "   <h2>Tiny Machine Learning</h2>\n"
             << "   <h2>Autonomous vessels</h2>"
             << "   <h2>Image segmentation</h2>"
             << "   <h3>Ragiology segmentation</h3>"
             << "   <h2>Local coworking space</h2>"
             << "  </body>\n"
             << "</html>\n";

        // Note: the fcgi_streambuf destructor will auto flush
    }

    // restore stdio streambufs
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

    return 0;
}
