#include "Requests.h"


// How it works
// Create request struct
// Create headers, url parameters, post parameters
// Add them to the request struct
// build the request struct
// send the request
// free all structs

int main(){
    Request* r = newRequest("POST","/");
    Header* h = newHeader("Authorization","somebase64==");
    BodyParameter* pass = newBodyParameter("password","supesuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodysuperlongcomplicatedpasswordnobodyrlongcomplicatedpasswordnobodycanguess!!!");
    addHeader(r,h);
    addBodyParameter(r,pass);
    buildRequest(r,"localhost");
    sendHttpRequest(r,"127.0.0.1",5000);


    // CLEANUP
    deleteHeader(h);
    deleteBodyParameter(pass);
    deleteRequest(r);
}
