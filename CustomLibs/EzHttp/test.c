#include "Requests.h"

// workflow
// new param, add param, build param
// at the end build request
// then send request

int main(){
    Request* r = newRequest("GET","/");
    //UrlParameter* u = newUrlParameter("user","tester");
    //UrlParameter* up = newUrlParameter("user","teesteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresteresterster");
    //addUrlParameter(r,u);
    //addUrlParameter(r,up);
    // build request runs all the builds on url post param and headers
    buildRequest(r);
    sendHttpRequest(r,"0.0.0.0",80);
}
