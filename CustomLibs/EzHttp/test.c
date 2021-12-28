#include "Requests.h"


// How it works
// Create request struct
// Create headers, url parameters, post parameters
// Add them to the request struct
// build the request struct
// send the request
// free all structs

int main(){
    Request* r = newRequest("GET","/");
    //Header* h = newHeader("Authorization","somebase64==");
    //BodyParameter* pass = newBodyParameter("password","supesuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodyrlongcomplicatedpasswordnobodycanguess!!!");
    //addHeader(r,h);
    //addBodyParameter(r,pass);
    buildRequest(r,"duckduckgo.com");
    //sendHttpRequest(r,"httpforever.com",80);
    sendHttpsRequest(r,"duckduckgo.com","443");


    // CLEANUP
    //deleteHeader(h);
    //deleteBodyParameter(pass);
    deleteRequest(r);
}
