#include <iostream>
#include "fcgio.h"

using namespace std;

// hijack (cout, cin and cerr for request handling)

int main(void) {

    // Backup the stdio streambufs (meaning?)
    streambuf * cin_streambuf = cin.rdbuf();
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
             << "<head>"
             << "<title>This is my voice</title>\n"
             << "</head>\n"
             << "<body>\n"
             << "<h1>Welcome MOFO!</h1>\n"
             << "</body>\n"
             << "</html>\n";

        // fcgi_streambuf destructor auto flushes

    }

    // restore stdio streambufs
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

    return 0;

}