from flask import Flask,request
import json

app = Flask(__name__)

@app.route("/",methods = ["POST","GET"])
def hello_world():
    if request.method == "POST":
        print(json.dumps(request.form))
    else:
        print(json.dumps(request.args))
    print(request.headers)
    return "<p>Hello, World!</p>"



if __name__ == "__main__":
    app.run(host="127.0.0.1",port=8443,ssl_context='adhoc')
