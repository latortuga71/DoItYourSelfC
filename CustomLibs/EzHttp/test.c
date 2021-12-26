#include "Requests.h"

// workflow
// new param, add param, build param
// at the end build request
// then send request

int main(){
    Request* r = newRequest("GET","/");
    Header* h = newHeader("Authorization","TESTER");
    //Header* hum = newHeader("Host","Latortuga71DesktopServer.com");
    addHeader(r,h);
    //addHeader(r,hum);
    //UrlParameter* up = newUrlParameter("user","teesteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresterster");
    //UrlParameter* u = newUrlParameter("user","tester");
    //addUrlParameter(r,u);
    //addUrlParameter(r,up);
    printHeaders(r);
    // build request runs all the builds on url post param and headers
    buildRequest(r,"localhost");
    sendHttpRequest(r,"127.0.0.1",5000);
    // cleanup always
    deleteHeader(h);
    deleteRequest(r);
}
